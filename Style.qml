pragma Singleton
import QtQuick 2.0

QtObject {

    property color topColor: "#1c6cff"
    property color bottomColor: "#c822ff"
    property color ctrlColor: "#143ca8"

    property int ctrlIconSize: 48

    property QtObject icons: QtObject {
        property string newFile: "qrc:/icons/gradient/icons8-new-video-file-64.png"
        property string backToStart: "qrc:/icons/gradient/icons8-back-to-start-64.png"
        property string play: "qrc:/icons/gradient/icons8-play-64.png"
        property string pause: "qrc:/icons/gradient/icons8-pause-64.png"
        property string resume: "qrc:/icons/gradient/icons8-resume-button-64.png"
        property string audioStreams: "qrc:/icons/gradient/icons8-audio-stream-64.png"
        property string volumeLow: "qrc:/icons/gradient/icons8-low-volume-64.png"
        property string volumeMid: "qrc:/icons/gradient/icons8-mid-volume-64.png"
        property string volumeMax: "qrc:/icons/gradient/icons8-max-volume-64.png"
        property string audioMute: "qrc:/icons/gradient/icons8-mute-audio-64.png"
        property string subtitles: "qrc:/icons/gradient/icons8-subtitles-64.png"
        property string settings: "qrc:/icons/gradient/icons8-settings-64.png"
    }

}
