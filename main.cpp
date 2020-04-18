/*  Piece of Cake - simple and easy to use video player
    Copyright (C) 2020  Herman Yulau

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QQuickItem>
#include <QRunnable>
#include <QQmlContext>

#include "player.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    Player player;
    qmlRegisterSingletonType(QUrl("qrc:/Style.qml"), "PieceOfCake.Style", 1, 0, "Style");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    QObject *videoItem;

    /* find and set the videoItem on the sink */
    videoItem = static_cast<QQuickWindow *> (engine.rootObjects().first())->findChild<QQuickItem *> ("videoItem");
    Q_ASSERT_X(videoItem, __FILE__, "videoItem is not found");
    player.setItemForSink(videoItem);

    // set object as context property to call from qml
//    SetPlaying *startPlay = new SetPlaying(pipeline);
    engine.rootContext()->setContextProperty("player", &player);

//    rootObject->scheduleRenderJob (new SetPlaying (pipeline),
//        QQuickWindow::BeforeSynchronizingStage);

    return app.exec();
}
