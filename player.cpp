#include "player.h"

Player::Player(QObject *parent) : QObject(parent)
{
    gstHnd.initGst();
}

void Player::setItemForSink(const QObject *item)
{
    gstHnd.setItemForSink(item);
}

void Player::play() const
{
    gstHnd.play();
}

void Player::pause() const
{
   gstHnd.pause();
}
