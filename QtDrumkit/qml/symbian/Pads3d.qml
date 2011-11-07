import QtQuick 1.0
import DrumEngine 1.0

import "../common"

Item {
    property alias pads: padItem

    // Pads are positioned to fixed 640x360 screen coordinates
    // according to the background. For the VGA background an y-offset
    // is required to adjust the pad coordinates.
    property int offset: screenVGA ? 100 : 0

    Image {
        id: img
        source: gfxPath + (screenVGA ? "3d/background_vga.png" : "3d/background.png")
    }

    Item {
        id: padItem
        anchors.fill:  parent

        Pad3d {
            x: 230*0.75
            y: 150*0.75 + offset
            sourceImage: gfxPath+"3d/tom1.png"
            sample: "tom1"
        }

        Pad3d {
            x: 365*0.75
            y: 140*0.75 + offset
            sourceImage: gfxPath+"3d/tom2.png"
            sample: "tom2"
        }

        Pad3d {
            x: 500*0.75
            y: 240*0.75 + offset
            sourceImage: gfxPath+"3d/tom3.png"
            sample: "tom3"
        }

        Pad3d {
            x: 10*0.75
            y: 240*0.75 + offset
            sourceImage: gfxPath+"3d/kick.png"
            sample: "kick"
        }

        Pad3d {
            x: 230*0.75
            y: 300*0.75 + offset
            sourceImage: gfxPath+"3d/snare.png"
            sample: "snare"
        }

        Pad3d {
            x: 430*0.75
            y: 355*0.75 + offset
            sourceImage: gfxPath+"3d/cowbell.png"
            sample: "cowbell"
        }


        Cymbal3d {
            x: 135*0.75
            y: 40*0.75 + offset
            initialAngle: 0
            targetAngle: 20
            rotateZ: 1
            sourceImage: gfxPath+"3d/china.png"
            sample: "china"
        }

        Cymbal3d {
            x: 0*0.75
            y: 90*0.75 + offset
            initialAngle: 0
            targetAngle: 20
            rotateZ: 1
            sourceImage: gfxPath+"3d/crash.png"
            sample: "crash"
        }

        Cymbal3d {
            x: 330*0.75
            y: 60*0.75 + offset
            initialAngle: 30
            targetAngle: 0
            rotateX: 1
            sourceImage: gfxPath+"3d/splash.png"
            sample: "splash"
        }

        Cymbal3d {
            x: 480*0.75
            y: 50*0.75 + offset
            initialAngle: 0
            targetAngle: -6
            rotateZ: 1
            sourceImage: gfxPath+"3d/ride2.png"
            sample: "ride2"
        }

        Cymbal3d {
            x: 565*0.75
            y: 115*0.75 + offset
            initialAngle: 0
            targetAngle: -6
            rotateZ: 1
            sourceImage: gfxPath+"3d/ride1.png"
            sample: "ride1"
        }

        Cymbal3d {
            x: 665*0.75
            y: 260*0.75 + offset
            initialAngle: 0
            targetAngle: -5
            rotateZ: 1
            sourceImage: gfxPath+"3d/hihatopenlower.png"
            sample: "hihat2"
        }

        Cymbal3d {
            x: 660*0.75
            y: 230*0.75 + offset
            initialAngle: 0
            targetAngle: -5
            rotateZ: 1
            sourceImage: gfxPath+"3d/hihatopenupper.png"
            sample: "hihat2"
        }


        Cymbal3d {
            x: 614*0.75
            y: 350*0.75 + offset
            initialAngle: 0
            targetAngle: -3
            rotateZ: 1
            sourceImage: gfxPath+"3d/hihatclosed.png"
            sample: "hihat1"
        }
    }

    Image {
        anchors.top: img.top
        source: gfxPath + (screenVGA ? "3d/locks_vga.png" : "3d/locks.png")
    }

}
