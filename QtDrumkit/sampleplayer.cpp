/**
 * Copyright (c) 2011 Nokia Corporation.
 * All rights reserved.
 *
 * Part of the QtDrumkit
 *
 * For the applicable distribution terms see the license text file included in
 * the distribution.
 */

#include <QtCore/QDebug>
#include <QStringList>
#include "sampleplayer.h"

#include "audiomixer.h"
#include "audiobuffer.h"
#include "audiobufferplayinstance.h"

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
    // Set a reasonable volume for the mixer.
    m_audioMixer.setAbsoluteVolume(3.0f / 10);

    // Prepare the sample map and generate preloaded buffers.
    QStringList samples;
    samples << "cowbell" << "crash" << "hihat1" << "hihat2" 
	    << "kick" << "ride1" << "ride2" << "snare" 
            << "splash" << "tom1" << "tom2" << "tom3" << "china";

    foreach (QString name, samples) {
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

#ifdef Q_OS_SYMBIAN
    m_volumeKeys = new VolumeKeys(this);
    connect(m_volumeKeys, SIGNAL(volumeKeyUp()),
            this, SLOT(volumeUp()));
    connect(m_volumeKeys, SIGNAL(volumeKeyDown()),
            this, SLOT(volumeDown()));
#endif


}

SamplePlayer::~SamplePlayer()
{
}

void SamplePlayer::play(GE::AudioBuffer *buffer) 
{
    // Play the AudioBuffer using mixer.
    Q_ASSERT(buffer);
    GE::AudioBufferPlayInstance* inst = buffer->playWithMixer(m_audioMixer);   
    if (inst == 0) {
        qWarning() << "playWithMixer failed";
    }
}

void SamplePlayer::playSample(QString name)
{
    // Fetch the buffer corresponding to the name and play it.
    play(m_samples[name]);
}

void SamplePlayer::volumeDown()
{
    m_audioIf->volumeDown();
}

void SamplePlayer::volumeUp()
{
    m_audioIf->volumeUp();
}
