/**
 * Copyright (c) 2011 Nokia Corporation.
 */

import QtQuick 1.0

// Button for selecting instruments.
// When focused, displays a highlight.
// When clicked, plays the corresponding instrument sample.
Item {
    id: container

    property string sample
    property string image
    property string imagePressed

    signal pressed

    Image {
        anchors.centerIn: parent
        id: img
        source: container.focus ? gfxPath + parent.imagePressed : gfxPath + parent.image
    }

    MouseArea {
        anchors.fill: img
        onPressed: {
            container.focus = true
            parent.pressed()
            engine.playSample(sample)
        }
    }
}
