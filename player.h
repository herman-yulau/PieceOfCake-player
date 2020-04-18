#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

#include "gsthandler.h"

class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = nullptr);

    void setItemForSink(const QObject *item);

    Q_INVOKABLE void play() const;

signals:

private:
    GstHandler gstHnd;
};

#endif // PLAYER_H
