#ifndef AUDIO_GAMEENABLER_H
#define AUDIO_GAMEENABLER_H

#include <QObject>
#include <QTimer>

#include "audiointerface.h"
#include "pullaudioout.h"
#include "audiomixer.h"

// Audio output using GameEnabler.
class AudioGameEnabler : public QObject,
        public AudioInterface
{
    Q_OBJECT;
public:
    explicit AudioGameEnabler(GE::AudioMixer& audioMixer, QObject *parent = 0);
    virtual ~AudioGameEnabler();

private:

    GE::PullAudioOut* m_audioOut;
    GE::AudioMixer& m_audioMixer;

#ifdef Q_OS_SYMBIAN
    // Used to tick the QtGameEnabler audio engine on Symbian
    QTimer m_audioPullTimer;
#endif
};

#endif 
