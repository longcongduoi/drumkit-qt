/**
 * Copyright (c) 2011 Nokia Corporation.
 */

import QtQuick 1.0
import DrumEngine 1.0

import "../common"

Item {
    Image {
        source: gfxPath + "background.png"
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

