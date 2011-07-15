import QtQuick 1.0
import DrumEngine 1.0

Item {
    width: 854
    height: 480

    Image {
        source: "gfx/drumpads.png"
    
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
            onPressed: {
                if(engine.isRecording) {
                    engine.stop()
                } else {
                    engine.record()
                }
            }
        }
        Button {
            id: playButton
            image: "gfx/play.png"
            imagePressed: "gfx/play_pressed.png"
            enabled: engine.canPlay && !engine.isRecording
            toggled: engine.isPlaying
            onPressed: {
                if(engine.isPlaying) {
                    engine.stop()
                } else {
                    engine.play()
                }
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

}
