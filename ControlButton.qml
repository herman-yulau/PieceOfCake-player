import QtQuick 2.0
import QtQuick.Controls 2.12

Button {
    id: controlButton
    property alias imageSrc: image.source

    contentItem: Image {
        id: image
        width: 16
        height: 16
//        fillMode: Image.PreserveAspectFit
    }
    background: Rectangle {
        color: "transparent"
        radius: width / 2;
        border.color: "black"
        border.width: 0

        MouseArea {
            anchors.fill: parent
            onPressedChanged: {
                parent.border.width = (pressed) ? 2 : 0;
            }
        }
    }
}
