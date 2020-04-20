#include "gsthandler.h"

#include <gst/gst.h>

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

void GstHandler::initGst()
{
    qDebug("gst init...");
    gst_init (NULL, NULL);

    pipeline = gst_parse_launch("uridecodebin uri=file:///home/herman/Videos/test_video.mkv name=file ! "                               // read file
                                "queue ! audioconvert ! audioresample ! autoaudiosink "                                                 // audio
                                "textoverlay name=sub1 shaded-background=yes valignment=bottom textoverlay name=sub2 valignment=top "   // elements for subs
                                "file.src_0 ! queue ! sub1.video_sink file.src_5 ! sub1.text_sink "                                     // video and sub track 1 to sub1
                                "file.src_4 ! sub2.text_sink "                                                                          // sub track 2 to sub2
                                "sub1. ! sub2.video_sink "                                                                              // video with sub1 to sub2
                                "sub2. ! videoconvert ! glupload ! qmlglsink name=qs", NULL);                                           // from sub2 to qmlglsink
}

void GstHandler::setItemForSink(const QObject *item)
{
    qDebug("Set item for sink");
    GstElement *qmlSink;
    qmlSink = gst_bin_get_by_name(GST_BIN(pipeline), "qs");
    g_assert(qmlSink);
    gst_object_unref (qmlSink);
    g_object_set(qmlSink, "widget", item, NULL);
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
