import QtQuick 2.14
import QtQuick.Controls 2.14

Slider {
    id: slider

    from: 0
    to: 100


    // style
    background: Rectangle {
        x: slider.leftPadding
        y: slider.topPadding + slider.availableHeight / 2 - height / 2
        implicitWidth: 200
        implicitHeight: 10
        width: slider.availableWidth
        height: implicitHeight
        radius: height / 2
        color: "#bdbebf"

        Rectangle {
            width: slider.visualPosition * parent.width
            height: parent.height
            radius: height / 2

            gradient: Gradient {
                orientation: Gradient.Horizontal
                GradientStop { position: 0; color: "#9e28d1" }
                GradientStop { position: 1; color: "#ff9500" }
            }
        }
    }

    handle: Rectangle {
        id: handle
        x: slider.leftPadding + slider.visualPosition * (slider.availableWidth - width)
        y: slider.topPadding + slider.availableHeight / 2 - height / 2
        width: 5
        height: 15
        radius: height / 2
    }
}
