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

    Image {
        source: gfxPath + "background.png"
    }

    Button {
        id: infoButton
        anchors.top:  parent.top
        anchors.left:  parent.left
        image: "info.png"
        imagePressed: "info_pressed.png"
        onPressed: info.show = true
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

    // Top row pads from left to right
    Pad {
        id: pad1
        x: 148; y: 60
        width: 180; height: 180
        sample: "crash"
    }

    Pad {
        id: pad2
        x: 340; y: 118
        width: 200; height: 200
        sample: "tom1"
    }

    Pad {
        id: pad3
        x: 550; y: 54
        width: 180; height: 180
        sample: "tom2"
    }

    // Bottom row
    Pad {
        id: pad4
        x: 30; y: 240
        width: 224; height: 224
        sample: "snare"
    }

    Pad {
        id: pad5
        x: 278; y: 318
        width: 152; height: 152
        sample: "hihat1"
    }

    Pad {
        id: pad6
        x: 466; y: 320
        width: 146; height: 146
        sample: "ride1"
    }

    Pad {
        id: pad7
        x: 630; y: 234
        width: 204; height: 204
        sample: "kick"
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
