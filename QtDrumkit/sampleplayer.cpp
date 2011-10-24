#include <QtCore/QDebug>
#include <QStringList>
#include "sampleplayer.h"

#ifndef Q_OS_SYMBIAN
#include "audiooutpulse.h"
#endif

using namespace GE;

SamplePlayer::SamplePlayer(QObject *parent) 
    : QThread(parent)
{
#ifndef PULSE
    m_audioOut = new AudioOut(&m_audioMixer, this);
#endif

    m_audioMixer.setAbsoluteVolume(3.0f / 10);

    // Prepare the sample map and generate preloaded buffers.
    QStringList samples;
    samples << "cowbell" << "crash" << "hihat1" << "hihat2" 
	    << "kick" << "ride1" << "ride2" << "snare" 
            << "splash" << "tom1" << "tom2" << "tom3" << "china";

    foreach(QString name, samples) {
        m_samples[name] = AudioBuffer::loadWav(":/samples/"+name+".wav", this);
    }

#ifdef Q_OS_SYMBIAN
    // On Symbian, a timer is required to drive the audio output.
    m_audioPullTimer.setInterval(5);
    connect(&m_audioPullTimer, SIGNAL(timeout()), m_audioOut, SLOT(tick()));
    m_audioPullTimer.start();
#endif

#ifdef PULSE
    // If using Pulse Audio, start the thread.
    start();
#endif
}


SamplePlayer::~SamplePlayer()
{
#ifdef Q_OS_SYMBIAN
    m_audioPullTimer.stop();
#endif

#ifdef PULSE
    // Stop Pulse Audio wait for the thread to exit.
    pulseOutDeinit();
    wait();
#endif
}

void SamplePlayer::play(AudioBuffer* buffer) 
{
    // Play the AudioBuffer using mixer.
    Q_ASSERT(buffer);
    AudioBufferPlayInstance* inst = buffer->playWithMixer(m_audioMixer);   
    if(inst == 0) {
        qWarning() << "playWithMixer failed";
    }
}

void SamplePlayer::playSample(QString name)
{
    // Fetch the buffer corresponding to the name and play it.
    play(m_samples[name]);
}


void SamplePlayer::run()
{
#ifdef PULSE
    // The thread initializes Pulse Audio and sits in a loop processing
    // audio.
    pulseOutInitialize(&m_audioMixer);
#endif
}


