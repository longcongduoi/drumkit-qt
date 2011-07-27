#ifndef SAMPLEPLAYER_H
#define SAMPLEPLAYER_H

#include <QObject>
#include <QVariant>
#include <QTimer>

#include "GEAudioOut.h"
#include "GEAudioMixer.h"
#include "GEAudioBuffer.h"
#include "GEAudioBufferPlayInstance.h"

// A class for playing samples.
class SamplePlayer : public QThread
{
    Q_OBJECT;
public:
    explicit SamplePlayer(QObject *parent = 0);
    virtual ~SamplePlayer();

public slots:

    // Plays a sample, where name is one of:
    // cowbell, crash, hihat1, hihat2, kick, ride1, ride2, snare,
    // splash, tom1, tom2, tom3
    void playSample(QString name);

private:
    //  Plays a sample described by GE::AudioBuffer.
    void play(GE::AudioBuffer* buffer);

    // From QThread. Used by Pulse Audio mode.
    virtual void run();

private:
    // Mixer for sample playback.
    GE::AudioMixer m_audioMixer;

    // Map of preloaded sample data.
    QMap<QString, GE::AudioBuffer*> m_samples;

#ifndef PULSE
    // If not using Pulse Audio, use the QtGameEnabler for output.
    GE::AudioOut* m_audioOut;
#endif

#ifdef Q_OS_SYMBIAN
    // Used to tick the QtGameEnabler audio engine on Symbian
    QTimer m_audioPullTimer;
#endif
};

#endif // SAMPLEPLAYER_H
