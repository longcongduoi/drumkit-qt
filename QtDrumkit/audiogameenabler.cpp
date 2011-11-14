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
#include "audiogameenabler.h"

#include "pushaudioout.h"
#include "pullaudioout.h"
#include "audiomixer.h"
#include "audiobuffer.h"
#include "audiobufferplayinstance.h"

/*!
 * \class AudioGameEnabler
 * \brief Audio output using GameEnabler.
 */
AudioGameEnabler::AudioGameEnabler(GE::AudioMixer &audioMixer, QObject *parent)
    : QObject(parent),
      m_audioMixer(audioMixer)
{
    m_audioOut = new GE::PullAudioOut(&m_audioMixer, this);
    
    if(m_audioOut->needsManualTick()) {
        // On Symbian, a timer is required to drive the audio output.
        m_audioPullTimer.setInterval(5);
        connect(&m_audioPullTimer, SIGNAL(timeout()),
                m_audioOut, SLOT(tick()));
        m_audioPullTimer.start();
    }
    qDebug() << "GameEnabler Audio initialized";
}


AudioGameEnabler::~AudioGameEnabler()
{
    if(m_audioOut->needsManualTick()) {
        m_audioPullTimer.stop();
    }
    qDebug() << "GameEnabler Audio deinitialized";
}

