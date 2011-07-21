import QtQuick 1.0

Item {
    property bool show: false

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

    MouseArea {
        anchors.fill: parent
        onPressed: show = false
    }

    Text {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        color: "white"
        font.pointSize: 18
        font.bold: true
        text: "Welcome to QtDrumkit!\n\n"+
              "Let your fills fly by tapping the pads.\n"+
              "You may also record your beats and play them afterwards.\n"+
              "Long tap on a pad lets you select different instruments.\n\n"+
              "Tap the screen to continue!"
        wrapMode: Text.WordWrap
        horizontalAlignment: Text.AlignHCenter
    }
}
