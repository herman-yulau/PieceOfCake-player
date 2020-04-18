import QtQuick 2.14
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {
    id: timeBox

    Rectangle {
        id: background

        anchors.fill: parent
        radius: 15
        gradient: Gradient {
            GradientStop { position: 0; color: "#5b1991" }
            GradientStop { position: 1; color: "#c812cf" }
        }

        border.color: "#9f0aa3"
        border.width: 1
    }

    RowLayout {
        id: rootLayout
        anchors.fill: parent
        anchors.centerIn: parent
        spacing: 0

        Label {
           id: timeElapsed
           Layout.leftMargin: 5
           color: "white"
           font.pixelSize: 12
           horizontalAlignment: Qt.AlignRight
           text: "00:00:00"
        }

        ToolSeparator {}

        Label {
           id: timeRemaining
           color: "white"
           font.pixelSize: timeElapsed.font.pixelSize
           text: "00:00:00"
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:40;width:120}
}
##^##*/
