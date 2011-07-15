
function play(sample) {
    switch(sample)
    {
    case "cowbell":
        DrumEngine.playCowbell();
        break;
    case "crash":
        DrumEngine.playCrash();
        break;
    case "hihat1":
        DrumEngine.playHihat1();
        break;
    case "hihat2":
        DrumEngine.playHihat2();
        break;
    case "kick":
        DrumEngine.playKick();
        break;
    case "ride1":
        DrumEngine.playRide1();
        break;
    case "ride2":
        DrumEngine.playRide2();
        break;
    case "snare":
        DrumEngine.playSnare();
        break;
    case "splash":
        DrumEngine.playSplash();
        break;
    case "tom1":
        DrumEngine.playTom1();
        break;
    case "tom2":
        DrumEngine.playTom2();
        break;
    case "tom3":
        DrumEngine.playTom3();
        break;
    }
}
