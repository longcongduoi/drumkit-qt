#ifndef AUDIO_PULSEAUDIO_H
#define AUDIO_PULSEAUDIO_H

#include <QObject>
#include <QThread>

#include "AudioInterface.h"
#include "GEAudioMixer.h"

// Audio output using PulseAudio, Linux desktop/Harmattan only.
class AudioPulseAudio : public QThread,
        public AudioInterface
{
    Q_OBJECT;
public:
    explicit AudioPulseAudio(GE::AudioMixer& audioMixer, QObject *parent = 0);
    virtual ~AudioPulseAudio();   

private:
    // From QThread. Used by Pulse Audio mode.
    void run();
    
    // From AudioInterface. Not needed as HW volume buttons do the work.
    void setVolume(int value) {}

    GE::AudioMixer& m_audioMixer;
};

#endif // SAMPLEPLAYER_H
