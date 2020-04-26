#include "gsthandler.h"

#include <gst/gst.h>

static void onPadAdded(GstElement *src, GstPad *new_pad, GstHandler *player);

GstHandler::GstHandler(QObject *parent) : QObject(parent)
{

}

GstHandler::~GstHandler()
{
    if (this->pipeline) {
        gst_element_set_state (pipeline, GST_STATE_NULL);
        gst_object_unref (pipeline);
    }

    gst_deinit ();
}

int GstHandler::initGst()
{
    qDebug("gst init...");
    GstElement *uridecodebin, *queue_audio, *audioconvert, *audioresample, *autoaudiosink, *firstSub,
               *secondSub, *queue_video, *videoconvert, *glupload, *glsinkbin, *qmlglsink;

    gst_init (NULL, NULL);

    // init all elements: element, name
    uridecodebin = gst_element_factory_make("uridecodebin", "dec");
    queue_audio = gst_element_factory_make("queue", "queue_audio");
    queue_video = gst_element_factory_make("queue", "queue_video");
    audioconvert = gst_element_factory_make("audioconvert", "audconv");
    audioresample = gst_element_factory_make("audioresample", "audres");
    autoaudiosink = gst_element_factory_make("autoaudiosink", "audiosink");
    firstSub = gst_element_factory_make("textoverlay", "first_sub");
    secondSub = gst_element_factory_make("textoverlay", "second_sub");
    videoconvert = gst_element_factory_make("videoconvert", "vidconv");
    glupload = gst_element_factory_make("glupload", "glupload");
    glsinkbin = gst_element_factory_make("glsinkbin", "sinkbin");
    qmlglsink = gst_element_factory_make("qmlglsink", "qsink");

    pipeline = gst_pipeline_new("pipeline");

    // init check
    if (!pipeline || !uridecodebin || !queue_audio || !queue_video || !audioconvert || !audioresample || !autoaudiosink ||
        !firstSub || !secondSub || !videoconvert || !glupload || !glsinkbin || !qmlglsink) {
        g_printerr ("Not all elements could be created.\n");
        gst_object_unref(pipeline);
        return -1;
    }

    // set sink in sink bin as qmlglsink
    g_object_set(glsinkbin, "sink", qmlglsink, NULL);

    // add all elements in the pipeline
    gst_bin_add_many(GST_BIN(pipeline), uridecodebin, queue_audio, queue_video, audioconvert, audioresample, autoaudiosink,
                     firstSub, secondSub, videoconvert, glupload, glsinkbin, NULL);

    // link audio
    if (gst_element_link_many(queue_audio, audioconvert, audioresample, autoaudiosink, NULL) != true) {
        g_printerr("Audio elements could not be linked.\n");
        gst_object_unref(pipeline);
        return -1;
    }

    // link video
    if (gst_element_link_many(queue_video, firstSub, secondSub, videoconvert, glsinkbin, NULL) != true) {
        g_printerr("Video elements could not be linked.\n");
        gst_object_unref(pipeline);
        return -1;
    }

    g_object_set(uridecodebin, "uri", "file:///home/herman/Videos/test_video.mkv", NULL);
    g_object_set(secondSub, "valignment", 2, NULL);
    /* Connect to the pad-added signal */
    g_signal_connect (uridecodebin, "pad-added", G_CALLBACK (onPadAdded), this);
//    pipeline = gst_parse_launch("uridecodebin uri=file:///home/herman/Videos/test_video.mkv name=file ! "                               // read file
//                                "queue ! audioconvert ! audioresample ! autoaudiosink "                                                 // audio
//                                "textoverlay name=sub1 shaded-background=yes valignment=bottom textoverlay name=sub2 valignment=top "   // elements for subs
//                                "file.src_0 ! queue ! sub1.video_sink file.src_5 ! sub1.text_sink "                                     // video and sub track 1 to sub1
//                                "file.src_4 ! sub2.text_sink "                                                                          // sub track 2 to sub2
//                                "sub1. ! sub2.video_sink "                                                                              // video with sub1 to sub2
//                                "sub2. ! videoconvert ! glupload ! qmlglsink name=qs", NULL);                                           // from sub2 to qmlglsink
    return 0;
}

void GstHandler::setItemForSink(const QObject *item)
{
    qDebug("Set item for sink");
    GstElement *qSink, *sinkbin;

    sinkbin = gst_bin_get_by_name(GST_BIN(pipeline), "sinkbin");
    g_assert(sinkbin);
    qSink = gst_bin_get_by_name(GST_BIN_CAST(sinkbin), "sink");
    g_assert(qSink);
    g_object_set(qSink, "widget", item, NULL);

    gst_object_unref (qSink);
    gst_object_unref (sinkbin);
}

GstElement *GstHandler::getPipeline() const
{
    return pipeline;
}

void GstHandler::play() const
{
    qDebug("play");
    if (this->pipeline)
        gst_element_set_state (this->pipeline, GST_STATE_PLAYING);
}

void GstHandler::pause() const
{
    qDebug("pause");
    if (this->pipeline)
        gst_element_set_state (this->pipeline, GST_STATE_PAUSED);
}

static void onPadAdded(GstElement *src, GstPad *new_pad, GstHandler *player) {
    GstPadLinkReturn ret;
    GstPad *sink_pad = NULL;
    GstCaps *new_pad_caps = NULL;
    GstStructure *new_pad_struct = NULL;
    const gchar *new_pad_type = NULL;

    /* Check the new pad's type */
    new_pad_caps = gst_pad_get_current_caps (new_pad);
    new_pad_struct = gst_caps_get_structure (new_pad_caps, 0);
    new_pad_type = gst_structure_get_name (new_pad_struct);

    g_print ("Received new pad '%s' from '%s' with type '%s':\n", GST_PAD_NAME (new_pad), GST_ELEMENT_NAME (src), new_pad_type);

    // audio pads
    if (g_str_has_prefix(new_pad_type, "audio/x-raw")) {

        sink_pad = gst_element_get_static_pad(gst_bin_get_by_name(GST_BIN(player->getPipeline()), "queue_audio"), "sink");

        /* If queue_audio is already linked, we have nothing to do here */
        if (gst_pad_is_linked(sink_pad)) {
            g_print("  Pad is already linked. Ignoring.\n");
            goto exit;
        }

        ret = gst_pad_link(new_pad, sink_pad);
        if (GST_PAD_LINK_FAILED (ret)) {
            g_print("  Link failed. Type is '%s'.\n", new_pad_type);
        } else {
            g_print("  Link succeeded (type '%s').\n", new_pad_type);
        }
        goto exit;
    }

    // video pads
    if (g_str_has_prefix(new_pad_type, "video/x-raw")) {

        sink_pad = gst_element_get_static_pad(gst_bin_get_by_name(GST_BIN(player->getPipeline()), "queue_video"), "sink");

        /* If queue_video is already linked, we have nothing to do here */
        if (gst_pad_is_linked(sink_pad)) {
            g_print("  Pad is already linked. Ignoring.\n");
            goto exit;
        }

        ret = gst_pad_link(new_pad, sink_pad);
        if (GST_PAD_LINK_FAILED (ret)) {
            g_print("  Link failed. Type is '%s'.\n", new_pad_type);
        } else {
            g_print("  Link succeeded (type '%s').\n", new_pad_type);
        }
        goto exit;
    }

    if (g_str_has_prefix(new_pad_type, "text/x-raw")) {

        if (strcmp(gst_pad_get_name(new_pad),"src_4") == 0) {
            sink_pad = gst_element_get_static_pad(gst_bin_get_by_name(GST_BIN(player->getPipeline()), "second_sub"), "text_sink");
        } else if (strcmp(gst_pad_get_name(new_pad), "src_5") == 0) {
            sink_pad = gst_element_get_static_pad(gst_bin_get_by_name(GST_BIN(player->getPipeline()), "first_sub"), "text_sink");
        } else goto exit;

        /* If queue_video is already linked, we have nothing to do here */
        if (gst_pad_is_linked(sink_pad)) {
            g_print("  Pad is already linked. Ignoring.\n");
            goto exit;
        }

        ret = gst_pad_link(new_pad, sink_pad);
        if (GST_PAD_LINK_FAILED (ret)) {
            g_print("  Link failed. Type is '%s'.\n", new_pad_type);
        } else {
            g_print("  Link succeeded (type '%s').\n", new_pad_type);
        }
        goto exit;
    }

    exit:
    /* Unreference the new pad's caps, if we got them */
    if (new_pad_caps != NULL)
        gst_caps_unref (new_pad_caps);

    /* Unreference the sink pad */
    if (sink_pad != NULL)
        gst_object_unref (sink_pad);
}
