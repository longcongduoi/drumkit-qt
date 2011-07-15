import QtQuick 1.0

Rectangle {
    width: 854
    height: 480

    color: "darkgray"

    Rectangle {
        id: rectangle1
        x: 550
        y: 9
        width: 80
        height: 80
        radius: width/2
        Text {
            anchors.centerIn: parent
            text: qsTr("X");
            font.pixelSize: 32
            font.bold: true
        }

        MouseArea {
            anchors.fill: parent
            onPressed: {
                Qt.quit();
            }
        }

    }

    Rectangle {
        id: rectangle2
        x: 39
        y: 86
        width: 100
        height: 100
        radius: width/2
        color: "#ffffff"
        MouseArea {
            anchors.fill: parent
            onPressed: {
                DrumEngine.playHihat1();
            }
        }
    }

    Rectangle {
        id: rectangle3
        x: 161
        y: 27
        width: 100
        height: 100
        radius: width/2
        color: "#ffffff"
        MouseArea {
            anchors.fill: parent
            onPressed: {
                DrumEngine.playHihat2();
            }
        }

    }

    Rectangle {
        id: rectangle4
        x: 291
        y: 27
        width: 100
        height: 100
        radius: width/2
        color: "#ffffff"
        MouseArea {
            anchors.fill: parent
            onPressed: {
                DrumEngine.playRide1();
            }
        }

    }

    Rectangle {
        id: rectangle5
        x: 416
        y: 86
        width: 100
        height: 100
        radius: width/2
        color: "#ffffff"
        MouseArea {
            anchors.fill: parent
            onPressed: {
                DrumEngine.playKick();
            }
        }

    }

    Rectangle {
        id: rectangle6
        x: 75
        y: 212
        width: 100
        height: 100
        radius: width/2
        color: "#ffffff"
        MouseArea {
            anchors.fill: parent
            onPressed: {
                DrumEngine.playSnare();
            }
        }

    }

    Rectangle {
        id: rectangle7
        x: 390
        y: 212
        width: 100
        height: 100
        radius: width/2
        color: "#ffffff"
        MouseArea {
            anchors.fill: parent
            onPressed: {
                DrumEngine.playTom1();
            }
        }

    }

    Rectangle {
        id: rectangle8
        x: 205
        y: 165
        width: 164
        height: 147
        color: "#ffffff"
        radius: width/2
        MouseArea {
            anchors.fill: parent
            onPressed: {
                DrumEngine.playCowbell();
            }
        }

    }
}
