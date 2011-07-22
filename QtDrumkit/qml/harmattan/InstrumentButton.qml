import QtQuick 1.0

Item {
    property string sample
    property string image
    property string imagePressed
    signal pressed

    id: container

    Image {
        anchors.centerIn: parent
        id: img
        source: container.focus ? parent.imagePressed : parent.image
    }

    MouseArea {
        id: ma
        anchors.fill: img
        enabled: parent.enabled
        onPressed: {
            container.focus = true
            parent.pressed()
            engine.playSample(sample)
        }
    }
}
