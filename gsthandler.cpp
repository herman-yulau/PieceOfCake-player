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

    pipeline = gst_parse_launch("videotestsrc ! glupload ! qmlglsink name=qs", NULL);

//    GstElement *src = gst_element_factory_make ("videotestsrc", NULL);
//    GstElement *glupload = gst_element_factory_make ("glupload", NULL);
    /* the plugin must be loaded before loading the qml file to register the
    * GstGLVideoItem qml item */
//    GstElement *sink = gst_element_factory_make ("qmlglsink", NULL);

//    g_assert (src && glupload && sink);

//    gst_bin_add_many (GST_BIN (pipeline), src, glupload, sink, NULL);
//    gst_element_link_many (src, glupload, sink, NULL);
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
