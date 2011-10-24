import QtQuick 1.0
import "../common"

Item {
    id: cymbal

    x: 135
    y: 40

    property real initialAngle: 0
    property real targetAngle: 20
    property real rotateX: 0
    property real rotateY: 0
    property real rotateZ: 1
    property string sourceImage: gfxPath+"3d/china.png"
    property string sample: "crash"

    function hit() {
        if(anim.running) {
            anim.stop()
        }
        anim.start()
    }

    Image {
        id: img
        source: cymbal.sourceImage
    }

    transform: Rotation {
        id: rotation
        origin.x: img.x + img.width/2
        origin.y: img.y + img.height/2
        axis.x: cymbal.rotateX
        axis.y: cymbal.rotateY
        axis.z: cymbal.rotateZ     // set axis.y to 1 to rotate around y-axis
        angle: cymbal.initialAngle    // the default angle
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
        anchors.fill: img
        sample: parent.sample
        onClicked: parent.hit()
    }
}
