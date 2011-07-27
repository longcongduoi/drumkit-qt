import QtQuick 1.0

// A button that displays an animation when not pressed.
// The animation is a png file where the frames are arranged
// on top of each other. The clip property is used to hide
// other parts of the image.
Item {
    id: anim

    property string animation
    property string imagePressed
    property int frameCount
    property int currentFrame: 0

    signal released

    clip: true

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
        x: 0
        y: -parent.height * parent.currentFrame
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
