#include <QtCore/QDebug>
#include "audiogameenabler.h"

#include "pushaudioout.h"
#include "pullaudioout.h"
#include "audiomixer.h"
#include "audiobuffer.h"
#include "audiobufferplayinstance.h"

AudioGameEnabler::AudioGameEnabler(GE::AudioMixer& audioMixer, QObject *parent)
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

