#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QQuickItem>
#include <QRunnable>
#include <QQmlContext>

#include <gst/gst.h>

class SetPlaying : public QObject
{
    Q_OBJECT
public:
  SetPlaying(GstElement *);
  ~SetPlaying();
public slots:
  Q_INVOKABLE void run ();

private:
  GstElement * pipeline_;
};

//--------- definitions
SetPlaying::SetPlaying (GstElement * pipeline)
{
  this->pipeline_ = pipeline ? static_cast<GstElement *> (gst_object_ref (pipeline)) : NULL;
}

SetPlaying::~SetPlaying ()
{
  if (this->pipeline_)
    gst_object_unref (this->pipeline_);
}

void
SetPlaying::run ()
{
  if (this->pipeline_)
    gst_element_set_state (this->pipeline_, GST_STATE_PLAYING);
}
// without this line class declaration in main doesn't work
#include "main.moc"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    int ret;

    gst_init (&argc, &argv);

    GstElement *pipeline = gst_parse_launch("videotestsrc ! glupload ! qmlglsink name=qs", NULL);

//    GstElement *src = gst_element_factory_make ("videotestsrc", NULL);
//    GstElement *glupload = gst_element_factory_make ("glupload", NULL);
    /* the plugin must be loaded before loading the qml file to register the
    * GstGLVideoItem qml item */
//    GstElement *sink = gst_element_factory_make ("qmlglsink", NULL);

//    g_assert (src && glupload && sink);

//    gst_bin_add_many (GST_BIN (pipeline), src, glupload, sink, NULL);
//    gst_element_link_many (src, glupload, sink, NULL);

    GstElement *sink;
    sink = gst_bin_get_by_name(GST_BIN(pipeline), "qs");
    g_assert(sink);
    gst_object_unref (sink);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    QQuickItem *videoItem;
    QQuickWindow *rootObject;

    /* find and set the videoItem on the sink */
    rootObject = static_cast<QQuickWindow *> (engine.rootObjects().first());
    videoItem = rootObject->findChild<QQuickItem *> ("videoItem");
    g_assert (videoItem);
    g_object_set(sink, "widget", videoItem, NULL);

    // set object as context property to call from qml
    SetPlaying *startPlay = new SetPlaying(pipeline);
    engine.rootContext()->setContextProperty("startPlay", startPlay);

//    rootObject->scheduleRenderJob (new SetPlaying (pipeline),
//        QQuickWindow::BeforeSynchronizingStage);

    ret = app.exec();

    delete  startPlay;

    gst_element_set_state (pipeline, GST_STATE_NULL);
    gst_object_unref (pipeline);

    gst_deinit ();

    return ret;
}
