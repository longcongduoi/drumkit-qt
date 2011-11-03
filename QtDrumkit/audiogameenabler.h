#ifndef AUDIO_GAMEENABLER_H
#define AUDIO_GAMEENABLER_H

#include <QObject>
#include <QTimer>

#include "audiointerface.h"
#include "pushaudioout.h"
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

    GE::PushAudioOut* m_audioOut;
    GE::AudioMixer& m_audioMixer;

    // Used to tick the QtGameEnabler audio engine on Symbian
    QTimer m_audioPullTimer;
};

#endif 
