#ifndef AUDIO_PULSEAUDIO_H
#define AUDIO_PULSEAUDIO_H

#include <QObject>
#include <QThread>
#include "GEAudioMixer.h"

// Audio output using PulseAudio, Linux desktop/Harmattan only.
class AudioPulseAudio : public QThread
{
    Q_OBJECT;
public:
    explicit AudioPulseAudio(GE::AudioMixer& audioMixer, QObject *parent = 0);
    virtual ~AudioPulseAudio();   

private:
    // From QThread. Used by Pulse Audio mode.
    void run();
    
    GE::AudioMixer& m_audioMixer;
};

#endif // SAMPLEPLAYER_H
