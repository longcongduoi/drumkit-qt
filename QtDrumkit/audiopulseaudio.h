/**
 * Copyright (c) 2011 Nokia Corporation.
 * All rights reserved.
 *
 * Part of the QtDrumkit
 *
 * For the applicable distribution terms see the license text file included in
 * the distribution.
 */

#ifndef AUDIO_PULSEAUDIO_H
#define AUDIO_PULSEAUDIO_H

#include <QObject>
#include <QThread>

#include "audiointerface.h"
#include "audiomixer.h"

/*!
 * \class AudioPulseAudio
 * \brief Audio output using PulseAudio, Linux desktop/Harmattan only.
 */
class AudioPulseAudio : public QThread,
                        public AudioInterface
{
    Q_OBJECT
public:
    explicit AudioPulseAudio(GE::AudioMixer &audioMixer, QObject *parent = 0);
    virtual ~AudioPulseAudio();   

private:
    // From QThread. Used by Pulse Audio mode.
    void run();
    
    GE::AudioMixer &m_audioMixer;
};

#endif // SAMPLEPLAYER_H
