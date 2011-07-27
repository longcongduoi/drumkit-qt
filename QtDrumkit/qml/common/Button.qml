import QtQuick 1.0

// A togglable button that can be enabled or disabled.
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
        source: parent.toggled || ma.pressed ? gfxPath + imagePressed : gfxPath + image
    }

    MouseArea {
        id: ma
        anchors.fill: img
        enabled: parent.enabled
        onPressed: parent.pressed()
        onReleased: parent.released()
    }
}
