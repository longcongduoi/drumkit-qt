import QtQuick 1.0

Item {

    property string sourceImage
    property string sample

    Image {
        id: img
        source: parent.sourceImage
        scale: pad.pressed ? 0.97 : 1.0
    }

    Pad {
        id: pad
        anchors.fill: img
        sample: parent.sample
        showSplash: false
    }
}
