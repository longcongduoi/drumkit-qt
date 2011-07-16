import QtQuick 1.0

Item {

    property string sample

    MouseArea {
        id: ma
        anchors.fill: parent
        onPressed: engine.playSample(sample)
    }

    Image {
        source: "gfx/splash.png"
        anchors.centerIn: parent
        visible: ma.pressed
    }
}
