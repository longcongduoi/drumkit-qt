import QtQuick 1.0

Item {
    property string sample
    property string image
    property string imagePressed
    signal clicked

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
        onClicked: {
            container.focus = true
            parent.clicked()
            engine.playSample(sample)
        }
    }
}
