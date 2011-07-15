import QtQuick 1.0

import "Drums.js" as Drums

Item {

    property string sample

    MouseArea {
        id: ma
        anchors.fill: parent;
        onClicked: engine.playSample(sample)
    }

    Image {
        source: "gfx/splash.png"
        anchors.centerIn: parent
        visible: ma.pressed
    }
}
