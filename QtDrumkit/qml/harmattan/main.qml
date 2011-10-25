import QtQuick 1.0
import DrumEngine 1.0

import "../common"

// Main screen for Harmattan devices (Nokia N9, N950).
Item {
    // This property is used to find the graphics in all components.
    property string gfxPath:  "../harmattan/gfx/"

    width: 854
    height: 480

    // DrumEngine instance for sample playing and drum track recording and playback.
    DrumEngine {
        id: engine
    }

    // UI components

    Flipable {
        id: flipable
        anchors.fill:  parent

        property bool flipped: false

        front: Pads2d {}
        back: Pads3d {
            // Mirror the back side so that after flipping the orientation ends up straight.
            transform: Rotation {
                origin.x: flipable.width/2
                origin.y: flipable.height/2
                axis.x: 0; axis.y: 1; axis.z: 0
                angle: 180
            }
        }

        transform: Rotation {
            id: rotation
            origin.x: flipable.width/2
            origin.y: flipable.height/2
            axis.x: 0; axis.y: 1; axis.z: 0
            angle: 0
        }

        states: State {
            PropertyChanges { target: rotation; angle: 180 }
            when: flipable.flipped
        }

        transitions: Transition {
            PropertyAnimation { target: rotation; property: "angle"; duration: 1000; easing.type: Easing.OutBack }
        }
    }


    Button {
        id: infoButton
        anchors.top:  parent.top
        anchors.left:  parent.left
        image: "info.png"
        imagePressed: "info_pressed.png"
        onPressed: info.show = true
    }

    Button {
        id: padButton
        anchors.top:  infoButton.bottom
        anchors.left:  parent.left
        image: flipable.flipped ? "pads.png" : "drumset.png"
        imagePressed: flipable.flipped ? "pads_pressed.png" : "drumset_pressed.png"
        onPressed: flipable.flipped = !flipable.flipped
    }


    Row {
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter

        Button {
            id: recButton
            image: "record.png"
            imagePressed: "record_pressed.png"
            enabled: engine.canRecord && !engine.isPlaying
            toggled: engine.isRecording
            visible: !engine.isRecording
            onReleased: engine.record()
        }

        AnimButton {
            animation: "recording.png"
            imagePressed: "record_pressed.png"
            frameCount: 20
            width: 103
            height: 103
            visible: !recButton.visible
            onReleased: engine.stop()
        }

        Button {
            id: playButton
            image: "play.png"
            imagePressed: "play_pressed.png"
            enabled: engine.canPlay && !engine.isRecording
            toggled: engine.isPlaying
            visible: !engine.isPlaying
            onReleased: engine.play()
        }
        Button {
            id: stopButton
            image: "stop.png"
            imagePressed: "stop_pressed.png"
            visible: !playButton.visible
            onReleased: engine.stop()
        }
    }

    Button {
        id: exitButton
        anchors.top:  parent.top
        anchors.right:  parent.right
        image: "exit.png"
        imagePressed: "exit_pressed.png"
        onReleased: Qt.quit()
    }


    InstrumentSelector {
        id: selector
        anchors.fill: parent
        radius: parent.height * 0.4
        show: false
        onSelected: show = false
    }

    Info {
        id: info
        anchors.fill: parent
        textPointSize: 18
        show: true
    }


}
