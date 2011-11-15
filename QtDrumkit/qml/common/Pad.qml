/**
 * Copyright (c) 2011 Nokia Corporation.
 */

import QtQuick 1.0

// Instrument pad component.
// Plays a specified sample when clicked.
// Opens the Instrument Selector on long tap, and reconfigures
// the sample to be played accordingly.
Item {
    id: container

    // Sample to be played by this pad.
    property string sample

    // Set to true when this pad has opened the Instrument Selector.
    property bool selectMode: false

    // Set to true if a highlight graphics should be shown when pressed.
    property bool showSplash: true

    property alias pressed: mouseArea.pressed  

    signal clicked

    function play() {
        engine.playSample(sample)
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onPressed: {
            if (simulator) {
                // Simulator specific! Play a sample with an ordinary mouse click.
                // Touch events are in available on simulator.
                play()
            }
            parent.clicked()
        }
        onPressAndHold: {
            // Disable instrument selection if engine
            // is doing playback or recording.
            if (!engine.isPlaying && !engine.isRecording) {
                selectMode = true
                // Show the Instrument Selector.
                // Set the origin coordinates according to this pad.

                // showSplash flag incidentally also indicates that the pad is used from the 3d
                // view. The coordinates need to be mapped to the selector coordinates,
                // which fills the main screen.
                if (!showSplash) {
                    var xy = mapToItem(selector, parent.x + parent.width/2, parent.y + parent.height/2)
                    selector.originX = xy.x
                    selector.originY = xy.y
                } else {
                    // No mapping needed, 2d-pad view.
                    selector.originX = parent.x + parent.width/2
                    selector.originY = parent.y + parent.height/2
                }
                selector.show = true
            }
        }
    }

    Image {
        id: img
        source: gfxPath + "splash.png"
        anchors.centerIn: parent
        visible: showSplash && mouseArea.pressed
    }

    // Instrument Selector signal connection to all pad instances.
    Connections {
        target: selector
        onSelected: {
            // Check if thes selector signal was targeted to this pad.
            if (selectMode && selector.selectedSample) {
                console.log("Changing " + sample + " to " + selector.selectedSample)
                sample = selector.selectedSample
                selectMode = false
            }
        }
    }
}
