#include <QtCore/QDebug>
#include "audiogameenabler.h"

#include "audioout.h"
#include "pushaudioout.h"
#include "audiomixer.h"
#include "audiobuffer.h"
#include "audiobufferplayinstance.h"

AudioGameEnabler::AudioGameEnabler(GE::AudioMixer& audioMixer, QObject *parent)
    : QObject(parent),
      m_audioMixer(audioMixer)
{
    m_audioOut = new GE::PushAudioOut(&m_audioMixer, this);
    
#ifdef Q_OS_SYMBIAN
    // On Symbian, a timer is required to drive the audio output.
    m_audioPullTimer.setInterval(5);
    connect(&m_audioPullTimer, SIGNAL(timeout()), m_audioOut, SLOT(tick()));
    m_audioPullTimer.start();
#endif
    qDebug() << "GameEnabler Audio initialized";
}


AudioGameEnabler::~AudioGameEnabler()
{
#ifdef Q_OS_SYMBIAN
    m_audioPullTimer.stop();
#endif
    qDebug() << "GameEnabler Audio deinitialized";
}

