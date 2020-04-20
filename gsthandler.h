#ifndef GSTHANDLER_H
#define GSTHANDLER_H

#include <QObject>
#include <gst/gst.h>

class GstHandler : public QObject
{
    Q_OBJECT
public:
    explicit GstHandler(QObject *parent = nullptr);
    ~GstHandler();

    void initGst();
    void setItemForSink(const QObject *item);

    void play() const;
    void pause() const;

signals:

private:
    GstElement *pipeline;
};

#endif // GSTHANDLER_H
