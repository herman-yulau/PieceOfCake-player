import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.14

import PieceOfCake.Style 1.0

Rectangle {
    id: root

    radius: height / 2
    color: Style.controlPanelColor

    RowLayout {
        id: rowLayout
        anchors.fill: parent

        ControlButton {
            id: btNewFile
            imageSrc: Style.icons.newFile
        }

        ControlButton {
            id: btBackToStart
            imageSrc: Style.icons.backToStart
        }
        ControlButton {
            id: btPlay
            imageSrc: Style.icons.play
        }
        ControlButton {
            id: btAudioStreams
            imageSrc: Style.icons.audioStreams
        }
        ControlButton {
            id: btSubtitles
            imageSrc: Style.icons.subtitles
        }
        ControlButton {
            id: btSettings
            imageSrc: Style.icons.settings
        }
    }
}
