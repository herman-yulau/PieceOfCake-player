import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.14

import PieceOfCake.Style 1.0

Item {
    id: root

    signal playClicked()
    signal pauseClicked()

    Rectangle {
        id: background

        anchors.fill: parent

//        radius: height / 2
        color: Style.ctrlColor
        opacity: 0.3
    }

    Timeline {
        id: timeline
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.topMargin: 5
    }

    RowLayout {
        id: rowPlay

        anchors.left: parent.left
        anchors.bottom: parent.bottom

        ControlButton {
            id: btBackToStart
            Layout.preferredHeight: Style.ctrlIconSize
            Layout.preferredWidth: Style.ctrlIconSize
            imageSrc: Style.icons.backToStart
        }

        ControlButton {
            id: btPlayPause
            Layout.preferredHeight: Style.ctrlIconSize * 1.2
            Layout.preferredWidth: Style.ctrlIconSize * 1.2
            imageSrc: Style.icons.play
            onClicked: {
                if (imageSrc == Style.icons.play) {
                    imageSrc = Style.icons.pause;
                    root.playClicked()
                } else {
                    imageSrc = Style.icons.play;
                    root.pauseClicked()
                }
            }
        }

        TimeBox {
            id: timebox
            Layout.preferredHeight: 40
            Layout.preferredWidth: 125
        }
    }

    RowLayout {
        id: rowTools

//        anchors.top: timeline.bottom
        anchors.bottom: parent.bottom
        anchors.right: parent.right

        ControlButton {
            id: btNewFile
            Layout.preferredHeight: Style.ctrlIconSize
            Layout.preferredWidth: Style.ctrlIconSize
            imageSrc: Style.icons.newFile
        }

        ControlButton {
            id: btVolume
            Layout.preferredHeight: Style.ctrlIconSize
            Layout.preferredWidth: Style.ctrlIconSize
            imageSrc: Style.icons.volumeMax
        }

        ControlButton {
            id: btAudioStreams
            Layout.preferredHeight: Style.ctrlIconSize
            Layout.preferredWidth: Style.ctrlIconSize
            imageSrc: Style.icons.audioStreams
        }

        ControlButton {
            id: btSubtitles
            Layout.preferredHeight: Style.ctrlIconSize
            Layout.preferredWidth: Style.ctrlIconSize
            imageSrc: Style.icons.subtitles
        }

        ControlButton {
            id: btSettings
            Layout.preferredHeight: Style.ctrlIconSize
            Layout.preferredWidth: Style.ctrlIconSize
            imageSrc: Style.icons.settings
        }
    }
}
