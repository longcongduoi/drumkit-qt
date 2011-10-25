import QtQuick 1.0

Item {
    id: pad

    property string sourceImage
    property string sample

    Image {
        id: img
        source: pad.sourceImage
    }

    Pad {
        anchors.fill: img
        sample: parent.sample
    }
}
