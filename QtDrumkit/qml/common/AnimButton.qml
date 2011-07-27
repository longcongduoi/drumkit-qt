import QtQuick 1.0

Item {
    id: anim
    property string animation
    property string imagePressed
    property int frameCount
    property int currentFrame: 0
    clip: true
    signal released

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
        source: gfxPath + animation
        y: -parent.height * parent.currentFrame
        x: 0
        visible: !ma.pressed
    }

    Image {
        source: gfxPath + imagePressed
        visible: ma.pressed
    }

    MouseArea {
        id: ma
        anchors.fill: parent
        enabled: parent.enabled
        onReleased: parent.released()
    }
}
