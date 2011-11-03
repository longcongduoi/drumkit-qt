#ifndef SAMPLEPLAYER_H
#define SAMPLEPLAYER_H

#include <QObject>
#include <QMap>

#include "audiointerface.h"
#include "audiomixer.h"
#include "audiobuffer.h"

// A class for playing samples.
class SamplePlayer : public QObject
{
    Q_OBJECT;
public:
    explicit SamplePlayer(QObject *parent = 0);
    virtual ~SamplePlayer();

public slots:

    // Plays a sample, where name is one of:
    // cowbell, crash, hihat1, hihat2, kick, ride1, ride2, snare,
    // splash, tom1, tom2, tom3, china.
    void playSample(QString name);

    // Sets volume, range 0..10.
    void setVolume(int value);

private:
    void play(GE::AudioBuffer* buffer);

    // Map of preloaded sample data.
    QMap<QString, GE::AudioBuffer*> m_samples;
    
    // Mixer audio source
    GE::AudioMixer m_audioMixer;

    // Interface to the audio output backend.
    AudioInterface* m_audioIf;
};

#endif // SAMPLEPLAYER_H
