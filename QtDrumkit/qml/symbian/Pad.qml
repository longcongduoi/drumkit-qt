import QtQuick 1.0

Item {

    property string sample
    property bool selectMode: false

    MouseArea {
        id: ma
        anchors.fill: parent
        onPressed: engine.playSample(sample)
        onPressAndHold: {
            selectMode = true
            // Selector should originate from this pad.
            selector.originX = parent.x + parent.width/2
            selector.originY = parent.y + parent.height/2
            selector.show = true
        }
    }

    Image {
        source: "gfx/splash.png"
        anchors.centerIn: parent
        visible: ma.pressed
    }

    Connections {
        target: selector
        onSelected: {
            if(selectMode && selector.selectedSample) {
                console.log("Changing " + sample + " to " + selector.selectedSample)
                sample = selector.selectedSample
                selectMode = false
            }
        }
    }
}
