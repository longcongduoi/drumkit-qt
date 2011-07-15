#include <QtCore/QDebug>
#include "drumengine.h"

using namespace GE;

DrumEngine::DrumEngine(QObject *parent) 
    : QObject(parent)
{

    m_audioOut = new AudioOut(&m_audioMixer, this);

#ifdef Q_OS_SYMBIAN
    m_audioPullTimer.setInterval(5);
    connect(&m_audioPullTimer, SIGNAL(timeout()), m_audioOut, SLOT(tick()));
    m_audioPullTimer.start();
#endif

//     for(int i=0; i<1; i++) {
// 	AudioBufferPlayInstance* player = new AudioBufferPlayInstance;
//  	player->setDestroyWhenFinished(false);
// 	m_players.append(player);
// 	m_audioMixer->addAudioSource(player);
//     }
// //     m_audioMixer->setAbsoluteVolume(3.0f / m_players.size());

//     m_audioMixer->setAbsoluteVolume(3.0f / 10);
    m_audioMixer.setGeneralVolume(0.1f);
    
    m_cowbell = AudioBuffer::loadWav(":/samples/cowbell.wav", this);
    m_crash = AudioBuffer::loadWav(":/samples/crash.wav", this);
    m_hihat1 = AudioBuffer::loadWav(":/samples/hihat1.wav", this);
    m_hihat2 = AudioBuffer::loadWav(":/samples/hihat2.wav", this);
    m_kick = AudioBuffer::loadWav(":/samples/kick.wav", this);
    m_ride1 = AudioBuffer::loadWav(":/samples/ride1.wav", this);
    m_ride2 = AudioBuffer::loadWav(":/samples/ride2.wav", this);
    m_snare = AudioBuffer::loadWav(":/samples/snare.wav", this);
    m_splash = AudioBuffer::loadWav(":/samples/splash.wav", this);
    m_tom1 = AudioBuffer::loadWav(":/samples/tom1.wav", this);
    m_tom2 = AudioBuffer::loadWav(":/samples/tom2.wav", this);
    m_tom3 = AudioBuffer::loadWav(":/samples/tom3.wav", this);
    
}


DrumEngine::~DrumEngine()
{
#ifdef Q_OS_SYMBIAN
    m_audioPullTimer.stop();
#endif

//     foreach (AudioBufferPlayInstance* player, m_players) {
// 	m_audioMixer->removeAudioSource(player);
// 	delete player;
//     }
}

void DrumEngine::play(AudioBuffer* buffer) {
    AudioBufferPlayInstance* inst = buffer->playWithMixer(m_audioMixer);
    if(inst) {
        qDebug() << "isPlaying:" << inst->isPlaying() << "isfinished:" << inst->isFinished();
    } else {
        qDebug() << "Play failed: no instance";
    }
    qDebug() << "Mixer source count:" << m_audioMixer.audioSourceCount();

//     AudioBufferPlayInstance* player = 0;
//     int i = 0;
//     foreach(AudioBufferPlayInstance* p, m_players) {
// 	if(!p->isPlaying()) {
// 	    player = p;
// 	    break;
// 	}
// 	i++;
//     }
//     if(player) {
// 	player->playBuffer(buffer);
// 	qDebug() << "Player" << i;
//     } else {
// 	qDebug() << "No available players";
//     }
}

void DrumEngine::playCowbell()
{
    play(m_cowbell);
    qDebug() << __PRETTY_FUNCTION__;
}
void DrumEngine::playCrash()
{
    play(m_crash);
    qDebug() << __PRETTY_FUNCTION__;
}
void DrumEngine::playHihat1()
{
    play(m_hihat1);
    qDebug() << __PRETTY_FUNCTION__;
}
void DrumEngine::playHihat2()
{
    play(m_hihat2);
    qDebug() << __PRETTY_FUNCTION__;
}
void DrumEngine::playKick()
{
    play(m_kick);
    qDebug() << __PRETTY_FUNCTION__;
}
void DrumEngine::playRide1()
{
    play(m_ride1);
    qDebug() << __PRETTY_FUNCTION__;
}
void DrumEngine::playRide2()
{
    play(m_ride2);
    qDebug() << __PRETTY_FUNCTION__;
}
void DrumEngine::playSnare()
{
    play(m_snare);
    qDebug() << __PRETTY_FUNCTION__;
}
void DrumEngine::playSplash()
{
    play(m_splash);
    qDebug() << __PRETTY_FUNCTION__;
}
void DrumEngine::playTom1()
{
    play(m_tom1);
    qDebug() << __PRETTY_FUNCTION__;
}
void DrumEngine::playTom2()
{
    play(m_tom2);
    qDebug() << __PRETTY_FUNCTION__;
}

void DrumEngine::playTom3()
{
    play(m_tom3);
    qDebug() << __PRETTY_FUNCTION__;
}

