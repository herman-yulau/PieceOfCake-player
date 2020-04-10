import QtQuick 2.14
import QtQuick.Window 2.14

import org.freedesktop.gstreamer.GLVideoItem 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Piece of Cake")

    Item {
        anchors.fill: parent

        GstGLVideoItem {
            id: video
            objectName: "videoItem"
            anchors.fill: parent

            MouseArea {
                id: mousearea
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    console.log("hit")
                    startPlay.run();
                }
            }
        }
    }
}
