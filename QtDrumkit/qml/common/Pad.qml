import QtQuick 1.0

Item {

    property string sample
    property bool selectMode: false

    MouseArea {
        id: ma
        anchors.fill: parent
        onPressed: engine.playSample(sample)
        onPressAndHold: {
            // Disable instrument selection if engine
            // is doing playback or recording.
            if(!engine.isPlaying && !engine.isRecording) {
               selectMode = true
               // Selector should originate from this pad coordinates.
               selector.originX = parent.x + parent.width/2
               selector.originY = parent.y + parent.height/2
               selector.show = true
            }
        }
    }

    Image {
        source: gfxPath + "splash.png"
        anchors.centerIn: parent
        visible: ma.pressed
    }

    Connections {
        target: selector
        onSelected: {
            // Check if thes selector signal was targeted to this pad.
            if(selectMode && selector.selectedSample) {
                console.log("Changing " + sample + " to " + selector.selectedSample)
                sample = selector.selectedSample
                selectMode = false
            }
        }
    }
}
