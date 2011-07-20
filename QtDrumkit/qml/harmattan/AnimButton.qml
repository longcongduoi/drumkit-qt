import QtQuick 1.0

Item {
    id: anim
    property string animation
    property string imagePressed
    property int frameCount
    property int currentFrame: 0
    clip: true
    signal pressed

    Timer {
        interval: 50
        running: parent.visible
        repeat: true
        onTriggered: {
            anim.currentFrame++
            anim.currentFrame %= anim.frameCount
        }
    }

    Image {
        source: animation
        y: -parent.height * parent.currentFrame
        x: 0
        visible: !ma.pressed
    }

    Image {
        source: imagePressed
        visible: ma.pressed
    }

    MouseArea {
        id: ma
        anchors.fill: parent
        enabled: parent.enabled
        onReleased: {
            parent.pressed()
        }
    }
}
