#ifndef AUDIO_GAMEENABLER_H
#define AUDIO_GAMEENABLER_H

#include <QObject>
#include <QTimer>

#include "audiointerface.h"
#include "GEAudioOut.h"
#include "GEAudioMixer.h"

// Audio output using GameEnabler.
class AudioGameEnabler : public QObject,
        public AudioInterface
{
    Q_OBJECT;
public:
    explicit AudioGameEnabler(GE::AudioMixer& audioMixer, QObject *parent = 0);
    virtual ~AudioGameEnabler();

private:
    void setVolume(int value) {}

    GE::AudioOut* m_audioOut;
    GE::AudioMixer& m_audioMixer;

#ifdef Q_OS_SYMBIAN
    // Used to tick the QtGameEnabler audio engine on Symbian
    QTimer m_audioPullTimer;
#endif
};

#endif 
