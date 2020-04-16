import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.14

import PieceOfCake.Style 1.0

Item {
    id: root

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
            id: btPlay
            Layout.preferredHeight: Style.ctrlIconSize * 1.2
            Layout.preferredWidth: Style.ctrlIconSize * 1.2
            imageSrc: Style.icons.play
        }
    }

    RowLayout {
        id: rowTools

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
