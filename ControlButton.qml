import QtQuick 2.12
import QtQuick.Controls 2.12

Button {
    id: controlButton

    signal clicked()

    property alias imageSrc: image.source

    contentItem: Image {
        id: image
        anchors.fill: parent
        anchors.margins: 3
        fillMode: Image.PreserveAspectFit
    }
    background: Rectangle {
        color: "transparent"
        radius: width / 2;
        opacity: 0.5

        MouseArea {
            anchors.fill: parent
            onClicked: controlButton.clicked()
            onPressedChanged: {
                parent.color = (pressed) ? "grey" : "transparent";
            }
        }
    }
}
