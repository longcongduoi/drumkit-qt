/**
 * Copyright (c) 2011 Nokia Corporation.
 */

import QtQuick 1.0

import "../common"

// 3d view
Item {

    property alias pads: padItem

    Image {
        source: gfxPath + "3d/background.png"
    }

    Item {
        id: padItem
        anchors.fill:  parent

        Pad3d {
            x: 230
            y: 150
            sourceImage: gfxPath+"3d/tom1.png"
            sample: "tom1"
        }

        Pad3d {
            x: 365
            y: 140
            sourceImage: gfxPath+"3d/tom2.png"
            sample: "tom2"
        }

        Pad3d {
            x: 500
            y: 240
            sourceImage: gfxPath+"3d/tom3.png"
            sample: "tom3"
        }

        Pad3d {
            x: 10
            y: 240
            sourceImage: gfxPath+"3d/kick.png"
            sample: "kick"
        }

        Pad3d {
            x: 230
            y: 300
            sourceImage: gfxPath+"3d/snare.png"
            sample: "snare"
        }

        Pad3d {
            x: 430
            y: 355
            sourceImage: gfxPath+"3d/cowbell.png"
            sample: "cowbell"
        }


        Cymbal3d {
            x: 135
            y: 40
            initialAngle: 0
            targetAngle: 20
            rotateZ: 1
            sourceImage: gfxPath+"3d/china.png"
            sample: "china"
        }

        Cymbal3d {
            x: 0
            y: 90
            initialAngle: 0
            targetAngle: 20
            rotateZ: 1
            sourceImage: gfxPath+"3d/crash.png"
            sample: "crash"
        }

        Cymbal3d {
            x: 330
            y: 60
            initialAngle: 30
            targetAngle: 0
            rotateX: 1
            sourceImage: gfxPath+"3d/splash.png"
            sample: "splash"
        }

        Cymbal3d {
            x: 480
            y: 50
            initialAngle: 0
            targetAngle: -6
            rotateZ: 1
            sourceImage: gfxPath+"3d/ride2.png"
            sample: "ride2"
        }

        Cymbal3d {
            x: 565
            y: 115
            initialAngle: 0
            targetAngle: -6
            rotateZ: 1
            sourceImage: gfxPath+"3d/ride1.png"
            sample: "ride1"
        }

        Cymbal3d {
            x: 665
            y: 260
            initialAngle: 0
            targetAngle: -5
            rotateZ: 1
            sourceImage: gfxPath+"3d/hihatopenlower.png"
            sample: "hihat2"
        }

        Cymbal3d {
            x: 660
            y: 230
            initialAngle: 0
            targetAngle: -5
            rotateZ: 1
            sourceImage: gfxPath+"3d/hihatopenupper.png"
            sample: "hihat2"
        }

        Cymbal3d {
            x: 614
            y: 350
            initialAngle: 0
            targetAngle: -3
            rotateZ: 1
            sourceImage: gfxPath+"3d/hihatclosed.png"
            sample: "hihat1"
        }
    }

    Image {
        source: gfxPath + "3d/locks.png"
    }

}
