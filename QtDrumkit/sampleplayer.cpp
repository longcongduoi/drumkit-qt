#include <QtCore/QDebug>
#include <QStringList>
#include "sampleplayer.h"

#include "GEAudioOut.h"
#include "GEAudioMixer.h"
#include "GEAudioBuffer.h"
#include "GEAudioBufferPlayInstance.h"

#ifdef USE_GAMEENABLER
#include "audiogameenabler.h"
#endif

#ifdef USE_DEVSOUND
#include "audiodevsound.h"
#endif

#ifdef USE_PULSEAUDIO
#include "audiopulseaudio.h"
#endif

SamplePlayer::SamplePlayer(QObject *parent) 
    : QObject(parent)
{
#ifdef Q_OS_SYMBIAN
    m_audioMixer.setAbsoluteVolume(3.0f / 10);
#else
    m_audioMixer.setAbsoluteVolume(3.0f / 10);
#endif

    // Prepare the sample map and generate preloaded buffers.
    QStringList samples;
    samples << "cowbell" << "crash" << "hihat1" << "hihat2" 
	    << "kick" << "ride1" << "ride2" << "snare" 
            << "splash" << "tom1" << "tom2" << "tom3" << "china";

    foreach(QString name, samples) {
        m_samples[name] = GE::AudioBuffer::loadWav(":/samples/"+name+".wav", this);
    }

#ifdef USE_GAMEENABLER
    m_audioIf = new AudioGameEnabler(m_audioMixer, this);
#endif
#ifdef USE_DEVSOUND
    m_audioIf = new AudioDevSound(m_audioMixer, this);
#endif
#ifdef USE_PULSEAUDIO
    m_audioIf = new AudioPulseAudio(m_audioMixer, this);
#endif
}


SamplePlayer::~SamplePlayer()
{
}

void SamplePlayer::play(GE::AudioBuffer* buffer) 
{
    // Play the AudioBuffer using mixer.
    Q_ASSERT(buffer);
    GE::AudioBufferPlayInstance* inst = buffer->playWithMixer(m_audioMixer);   
    if(inst == 0) {
        qWarning() << "playWithMixer failed";
    }
}

void SamplePlayer::playSample(QString name)
{
    // Fetch the buffer corresponding to the name and play it.
    play(m_samples[name]);
}

void SamplePlayer::setVolume(int value)
{
    m_audioIf->setVolume(value);
}
