import QtQuick 2.14
import QtQuick.Window 2.14

import org.freedesktop.gstreamer.GLVideoItem 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Piece of Cake")
    color: "gray"

    Rectangle {
        id: background
        anchors.fill: parent
        gradient: Gradient {
            GradientStop { position: 0.0; color: Style.topColor }
            GradientStop { position: 1.0; color: Style.bottomColor }
        }
    }

    Item {
        anchors.fill: parent

        GstGLVideoItem {
            id: video
            objectName: "videoItem"
//            anchors.fill: parent

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

    ControlPanel {
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 3
        height: 90
    }

    Shortcut {
       sequence: StandardKey.Quit
       onActivated: Qt.quit()
    }
}
