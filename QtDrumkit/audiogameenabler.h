/**
 * Copyright (c) 2011 Nokia Corporation.
 * All rights reserved.
 *
 * Part of the QtDrumkit
 *
 * For the applicable distribution terms see the license text file included in
 * the distribution.
 */

#ifndef AUDIO_GAMEENABLER_H
#define AUDIO_GAMEENABLER_H

#include <QObject>
#include <QTimer>

#include "audiointerface.h"
#include "pullaudioout.h"
#include "audiomixer.h"

/*!
 * \class AudioGameEnabler
 * \brief Audio output using GameEnabler.
 */
class AudioGameEnabler : public QObject,
                         public AudioInterface
{
    Q_OBJECT
public:
    explicit AudioGameEnabler(GE::AudioMixer &audioMixer, QObject *parent = 0);
    virtual ~AudioGameEnabler();

private:

    GE::PullAudioOut *m_audioOut;
    GE::AudioMixer &m_audioMixer;

    // Used to tick the QtGameEnabler audio engine on Symbian
    QTimer m_audioPullTimer;
};

#endif 
