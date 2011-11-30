/**
 * Copyright (c) 2011 Nokia Corporation.
 */

import QtQuick 1.0

// Cymbal pad for the 3d view. Provides a configurable swinging animation
// when hit.
Item {
    id: cymbal

    width: img.width
    height: img.height

    property real initialAngle: 0
    property real targetAngle: 0
    property real rotateX: 0
    property real rotateY: 0
    property real rotateZ: 0
    property alias sourceImage: img.source
    property alias sample: pad.sample

    function play() {
        pad.play()
    }

    function hit() {
        if (anim.running) {
            anim.stop()
        }
        anim.start()
    }

    Image {
        id: img
    }

    transform: Rotation {
        id: rotation
        origin.x: img.x + img.width/2
        origin.y: img.y + img.height/2
        axis.x: cymbal.rotateX
        axis.y: cymbal.rotateY
        axis.z: cymbal.rotateZ
        angle: cymbal.initialAngle
    }

    SequentialAnimation {
        id: anim
        NumberAnimation {
            target: rotation
            property: "angle"
            from: cymbal.initialAngle
            to: cymbal.targetAngle
            duration: 100
            easing.type: Easing.OutCubic
        }
        NumberAnimation {
            target: rotation
            property: "angle"
            to:  cymbal.initialAngle
            duration: 400
            easing.type: Easing.InOutCubic
        }
    }

    Pad {
        id: pad
        anchors.fill: img
        showSplash: false
        onClicked: parent.hit()
    }
}
