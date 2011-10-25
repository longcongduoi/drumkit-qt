import QtQuick 1.0
import DrumEngine 1.0

import "../common"

Item {
    Image {
        source: gfxPath + "3d/background.png"
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
        initialAngle: 40
        targetAngle: 0
        rotateX: 1
        sourceImage: gfxPath+"3d/splash.png"
        sample: "splash"
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


    Image {
        source: gfxPath + "3d/locks.png"
    }

}
