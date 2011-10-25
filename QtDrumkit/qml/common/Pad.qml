import QtQuick 1.0

// Instrument pad component.
// Plays a specified sample when clicked.
// Opens the Instrument Selector on long tap, and reconfigures
// the sample to be played accordingly.
Item {
    // Sample to be played by this pad.
    property string sample

    // Set to true when this pad has opened the Instrument Selector.
    property bool selectMode: false

    // Set to true if a highlight graphics should be shown when pressed.
    property bool showSplash: true

    property alias pressed: ma.pressed

    signal clicked

    MouseArea {
        id: ma
        anchors.fill: parent
        onPressed: {
            parent.clicked()
            engine.playSample(sample)
        }
        onPressAndHold: {
            // Disable instrument selection if engine
            // is doing playback or recording.
            if(!engine.isPlaying && !engine.isRecording) {
               selectMode = true
               // Show the Instrument Selector.
               // Set the origin coordinates according to this pad.
               selector.originX = parent.x + parent.width/2
               selector.originY = parent.y + parent.height/2
                console.log("Selector origin: "+ selector.originX + " " + selector.originY)
               selector.show = true
            }
        }
    }

    Image {
        source: gfxPath + "splash.png"
        anchors.centerIn: parent
        visible: showSplash && ma.pressed
    }

    // Instrument Selector signal connection to all pad instances.
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
