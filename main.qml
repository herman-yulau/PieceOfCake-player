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

    GstGLVideoItem {
        id: video
        objectName: "videoItem"
        anchors.fill: parent
    }

    ControlPanel {
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 3
        height: 80

        onPlayClicked: player.play()
        onPauseClicked: player.pause()
    }

    Shortcut {
       sequence: StandardKey.Quit
       onActivated: Qt.quit()
    }
}
