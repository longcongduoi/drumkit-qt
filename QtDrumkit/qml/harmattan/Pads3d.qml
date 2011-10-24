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
        rotateX: 0
        rotateY: 0
        rotateZ: 1
        sourceImage: gfxPath+"3d/china.png"
        sample: "china"
    }

    Cymbal3d {
        x: 0
        y: 100
        initialAngle: 0
        targetAngle: 20
        rotateX: 0
        rotateY: 0
        rotateZ: 1
        sourceImage: gfxPath+"3d/crash.png"
        sample: "crash"
    }

    Cymbal3d {
        x: 330
        y: 60
        initialAngle: 360
        targetAngle: 300
        rotateX: 1
        rotateY: 0
        rotateZ: 0
        sourceImage: gfxPath+"3d/splash.png"
        sample: "splash"
    }

    Image {
        source: gfxPath + "3d/locks.png"
    }

}
