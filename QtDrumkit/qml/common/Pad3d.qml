import QtQuick 1.0

Item {
    width: img.width
    height: img.height

    property string sourceImage
    property string sample

    function play() {
        pad.play()
    }

    Image {
        id: img
        source: parent.sourceImage
        scale: pad.pressed ? 0.9 : 1.0
        Behavior on scale { SpringAnimation { spring: 5; damping: 0.2 } }
    }

    Pad {
        id: pad
        anchors.fill: img
        sample: parent.sample
        showSplash: false
    }
}
