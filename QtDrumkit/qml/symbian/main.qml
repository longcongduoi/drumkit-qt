import QtQuick 1.0
import DrumEngine 1.0

import "../common"

Item {
    width: 640
    height: 360

    property string gfxPath:  "../symbian/gfx/"

    Image {
        source: "gfx/background.png"
    }

    DrumEngine {
        id: engine
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
            frameCount: 18
            width: 77
            height: 77
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
        x: 148*0.75; y: 60*0.75
        width: 180*0.75; height: 180*0.75
        sample: "crash"
    }

    Pad {
        id: pad2
        x: 340*0.75; y: 118*0.75
        width: 200*0.75; height: 200*0.75
        sample: "tom1"
    }

    Pad {
        id: pad3
        x: 550*0.75; y: 54*0.75
        width: 180*0.75; height: 180*0.75
        sample: "tom2"
    }

    // Bottom row
    Pad {
        id: pad4
        x: 30*0.75; y: 240*0.75
        width: 224*0.75; height: 224*0.75
        sample: "snare"
    }

    Pad {
        id: pad5
        x: 278*0.75; y: 318*0.75
        width: 152*0.75; height: 152*0.75
        sample: "hihat1"
    }

    Pad {
        id: pad6
        x: 466*0.75; y: 320*0.75
        width: 146*0.75; height: 146*0.75
        sample: "ride1"
    }

    Pad {
        id: pad7
        x: 630*0.75; y: 234*0.75
        width: 204*0.75; height: 204*0.75
        sample: "kick"
    }

    // Instrument selector is last so it will get mouse events first when shown.
    InstrumentSelector {
        id: selector
        anchors.fill:  parent
        radius: parent.height * 0.4
        show: false
        onSelected: show = false
    }

    Info {
        id: info
        anchors.fill: parent
	show: true
    }
}
