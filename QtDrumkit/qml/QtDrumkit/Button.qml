import QtQuick 1.0

Item {
    property string image;
    property string imagePressed
    property bool enabled: true
    property bool toggled: false
    signal pressed
    signal released

    width: childrenRect.width
    height: childrenRect.height
    opacity: enabled ? 1 : 0.5

    Image {
        id: img
        source: parent.toggled || ma.pressed ? parent.imagePressed : parent.image
    }

    MouseArea {
        id: ma
        anchors.fill: img
        enabled: parent.enabled
        onReleased: {
            parent.pressed()
        }
    }
}
