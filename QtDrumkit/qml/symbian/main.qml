import QtQuick 1.0
import DrumEngine 1.0

Item {
    width: 640
    height: 360

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
        image: "gfx/info.png"
        imagePressed: "gfx/info_pressed.png"
    }

    Row {
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter

        Button {
            id: recButton
            image: "gfx/record.png"
            imagePressed: "gfx/record_pressed.png"
            enabled: engine.canRecord && !engine.isPlaying
            toggled: engine.isRecording
            visible: !engine.isRecording
            onPressed: {
                engine.record()
            }
        }

        AnimButton {
            animation: "gfx/recording.png"
            imagePressed: "gfx/record_pressed.png"
            frameCount: 18
            width: 77
            height: 77
            visible: !recButton.visible
            onPressed: {
                engine.stop()
            }
        }

        Button {
            id: playButton
            image: "gfx/play.png"
            imagePressed: "gfx/play_pressed.png"
            enabled: engine.canPlay && !engine.isRecording
            toggled: engine.isPlaying
            visible: !engine.isPlaying
            onPressed: {
                engine.play()
            }
        }
        Button {
            id: stopButton
            image: "gfx/stop.png"
            imagePressed: "gfx/stop_pressed.png"
            visible: !playButton.visible
            onPressed: {
                engine.stop()
            }
        }
    }

    Button {
        id: exitButton
        anchors.top:  parent.top
        anchors.right:  parent.right
        image: "gfx/exit.png"
        imagePressed: "gfx/exit_pressed.png"
        onPressed: Qt.quit()
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

}
