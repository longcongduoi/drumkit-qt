import QtQuick 1.0

Item {
    property bool show: false
    property int radius: 100
    property string selectedSample
    signal selected

    property int originX: width/2
    property int originY: height/2

    id: container

    state: show ? "end" : "start"
    opacity: show ? 1.0 : 0

    Behavior on opacity {
        PropertyAnimation { duration: 700; easing {type: Easing.OutQuad} }
    }

    // Dim background
    Rectangle {
        anchors.fill: parent
        color: "black"
        opacity: 0.5
    }

    // Prevent mouse events
    MouseArea
    {
        anchors.fill: parent
    }

    Button {
        image: "gfx/selector/close.png"
        imagePressed: "gfx/selector/close.png"
        anchors.centerIn: parent
        onPressed: parent.selected()
    }

    FocusScope {
        id: buttons

        property int centerX
        property int centerY
        transform: [ Translate { x:buttons.centerX; y:buttons.centerY }, 
                     Rotation  { id:rotation; origin.x:buttons.centerX; origin.y:buttons.centerY} ]

        InstrumentButton {
            id: button1
            image: "gfx/selector/cowbell.png"
            imagePressed: "gfx/selector/cowbell_highlight.png"
            sample: "cowbell"
            onPressed: container.selectedSample = sample
        }
        InstrumentButton {
            id: button2
            image: "gfx/selector/crash.png"
            imagePressed: "gfx/selector/crash_highlight.png"
            sample: "crash"
            onPressed: container.selectedSample = sample
        }
        InstrumentButton {
            id: button3
            image: "gfx/selector/hihat1.png"
            imagePressed: "gfx/selector/hihat1_highlight.png"
            sample: "hihat1"
            onPressed: container.selectedSample = sample
        }
        InstrumentButton {
            id: button4
            image: "gfx/selector/hihat2.png"
            imagePressed: "gfx/selector/hihat2_highlight.png"
            sample: "hihat2"
            onPressed: container.selectedSample = sample
        }
        InstrumentButton {
            id: button5
            image: "gfx/selector/kick.png"
            imagePressed: "gfx/selector/kick_highlight.png"
            sample: "kick"
            onPressed: container.selectedSample = sample
        }
        InstrumentButton {
            id: button6
            image: "gfx/selector/ride1.png"
            imagePressed: "gfx/selector/ride1_highlight.png"
            sample: "ride1"
            onPressed: container.selectedSample = sample
        }
        InstrumentButton {
            id: button7
            image: "gfx/selector/ride2.png"
            imagePressed: "gfx/selector/ride2_highlight.png"
            sample: "ride2"
            onPressed: container.selectedSample = sample
        }
        InstrumentButton {
            id: button8
            image: "gfx/selector/snare.png"
            imagePressed: "gfx/selector/snare_highlight.png"
            sample: "snare"
            onPressed: container.selectedSample = sample
        }
        InstrumentButton {
            id: button9
            image: "gfx/selector/splash.png"
            imagePressed: "gfx/selector/splash_highlight.png"
            sample: "splash"
            onPressed: container.selectedSample = sample
        }
        InstrumentButton {
            id: button10
            image: "gfx/selector/tom1.png"
            imagePressed: "gfx/selector/tom1_highlight.png"
            sample: "tom1"
            onPressed: container.selectedSample = sample
        }
        InstrumentButton {
            id: button11
            image: "gfx/selector/tom2.png"
            imagePressed: "gfx/selector/tom2_highlight.png"
            sample: "tom2"
            onPressed: container.selectedSample = sample
        }
        InstrumentButton {
            id: button12
            image: "gfx/selector/tom3.png"
            imagePressed: "gfx/selector/tom3_highlight.png"
            sample: "tom3"
            onPressed: container.selectedSample = sample
        }

    }

    states: [
        State {
            name: "start"
            PropertyChanges { target: buttons; centerX: originX; centerY: originY }
            PropertyChanges { target: rotation; angle: 180 }
            PropertyChanges { target: button1; x: 0; y: 0 }
            PropertyChanges { target: button2; x: 0; y: 0 }
            PropertyChanges { target: button3; x: 0; y: 0 }
            PropertyChanges { target: button4; x: 0; y: 0 }
            PropertyChanges { target: button5; x: 0; y: 0 }
            PropertyChanges { target: button6; x: 0; y: 0 }
            PropertyChanges { target: button7; x: 0; y: 0 }
            PropertyChanges { target: button8; x: 0; y: 0 }
            PropertyChanges { target: button9; x: 0; y: 0 }
            PropertyChanges { target: button10; x: 0; y: 0 }
            PropertyChanges { target: button11; x: 0; y: 0 }
            PropertyChanges { target: button12; x: 0; y: 0 }
        },
        State {
            name: "end"
            PropertyChanges { target: buttons; centerX: container.width/2; centerY: container.height/2 }
            PropertyChanges { target: rotation; angle: 0 }
            PropertyChanges { target: button1; x: xPos(360/12*0); y: yPos(360/12*0) }
            PropertyChanges { target: button2; x: xPos(360/12*1); y: yPos(360/12*1) }
            PropertyChanges { target: button3; x: xPos(360/12*2); y: yPos(360/12*2) }
            PropertyChanges { target: button4; x: xPos(360/12*3); y: yPos(360/12*3) }
            PropertyChanges { target: button5; x: xPos(360/12*4); y: yPos(360/12*4) }
            PropertyChanges { target: button6; x: xPos(360/12*5); y: yPos(360/12*5) }
            PropertyChanges { target: button7; x: xPos(360/12*6); y: yPos(360/12*6) }
            PropertyChanges { target: button8; x: xPos(360/12*7); y: yPos(360/12*7) }
            PropertyChanges { target: button9; x: xPos(360/12*8); y: yPos(360/12*8) }
            PropertyChanges { target: button10; x: xPos(360/12*9); y: yPos(360/12*9) }
            PropertyChanges { target: button11; x: xPos(360/12*10); y: yPos(360/12*10) }
            PropertyChanges { target: button12; x: xPos(360/12*11); y: yPos(360/12*11) }
        }
    ]

    transitions: Transition {
        PropertyAnimation { duration: 700; target: buttons; properties: "centerX,centerY"; easing {type: Easing.OutQuad} }
        PropertyAnimation { duration: 700; target: rotation; properties: "angle"; easing {type: Easing.OutQuad} }
        PropertyAnimation { duration: 700; target: button1; properties: "x,y"; easing {type: Easing.OutQuad} }
        PropertyAnimation { duration: 700; target: button2; properties: "x,y"; easing {type: Easing.OutQuad} }
        PropertyAnimation { duration: 700; target: button3; properties: "x,y"; easing {type: Easing.OutQuad} }
        PropertyAnimation { duration: 700; target: button4; properties: "x,y"; easing {type: Easing.OutQuad} }
        PropertyAnimation { duration: 700; target: button5; properties: "x,y"; easing {type: Easing.OutQuad} }
        PropertyAnimation { duration: 700; target: button6; properties: "x,y"; easing {type: Easing.OutQuad} }
        PropertyAnimation { duration: 700; target: button7; properties: "x,y"; easing {type: Easing.OutQuad} }
        PropertyAnimation { duration: 700; target: button8; properties: "x,y"; easing {type: Easing.OutQuad} }
        PropertyAnimation { duration: 700; target: button9; properties: "x,y"; easing {type: Easing.OutQuad} }
        PropertyAnimation { duration: 700; target: button10; properties: "x,y"; easing {type: Easing.OutQuad} }
        PropertyAnimation { duration: 700; target: button11; properties: "x,y"; easing {type: Easing.OutQuad} }
        PropertyAnimation { duration: 700; target: button12; properties: "x,y"; easing {type: Easing.OutQuad} }
    }

    function xPos(angle) {
        return Math.cos(2*Math.PI/360*angle) * radius
    }
    function yPos(angle) {
        return Math.sin(2*Math.PI/360*angle) * radius
    }
}
