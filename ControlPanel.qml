import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.14

import PieceOfCake.Style 1.0

Item {
    id: root

    Rectangle {
        id: background

        anchors.fill: parent

        radius: height / 2
        color: Style.ctrlColor
        opacity: 0.5
    }

    RowLayout {
        id: rowLayout
        anchors.fill: parent

        ControlButton {
            id: btNewFile
            Layout.maximumHeight: Style.ctrlIconSize
            Layout.maximumWidth: Style.ctrlIconSize
            imageSrc: Style.icons.newFile
        }

        ControlButton {
            id: btBackToStart
            Layout.maximumHeight: Style.ctrlIconSize
            Layout.maximumWidth: Style.ctrlIconSize
            imageSrc: Style.icons.backToStart
        }
        ControlButton {
            id: btPlay
            Layout.maximumHeight: Style.ctrlIconSize
            Layout.maximumWidth: Style.ctrlIconSize
            imageSrc: Style.icons.play
        }
        ControlButton {
            id: btVolume
            Layout.maximumHeight: Style.ctrlIconSize
            Layout.maximumWidth: Style.ctrlIconSize
            imageSrc: Style.icons.volumeMax
        }
        ControlButton {
            id: btAudioStreams
            Layout.maximumHeight: Style.ctrlIconSize
            Layout.maximumWidth: Style.ctrlIconSize
            imageSrc: Style.icons.audioStreams
        }
        ControlButton {
            id: btSubtitles
            Layout.maximumHeight: Style.ctrlIconSize
            Layout.maximumWidth: Style.ctrlIconSize
            imageSrc: Style.icons.subtitles
        }
        ControlButton {
            id: btSettings
            Layout.maximumHeight: Style.ctrlIconSize
            Layout.maximumWidth: Style.ctrlIconSize
            imageSrc: Style.icons.settings
        }
    }
}
