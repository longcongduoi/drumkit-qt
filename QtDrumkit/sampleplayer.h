#ifndef SAMPLEPLAYER_H
#define SAMPLEPLAYER_H

#include <QObject>
#include <QVariant>
#include <QTimer>

#include "GEAudioOut.h"
#include "GEAudioMixer.h"
#include "GEAudioBuffer.h"
#include "GEAudioBufferPlayInstance.h"

// class SamplePlayer : public QObject
class SamplePlayer : public QThread
{
    Q_OBJECT;
public:
    explicit SamplePlayer(QObject *parent = 0);
    virtual ~SamplePlayer();

public slots:
    void playSample(QString name);

private:
    void play(GE::AudioBuffer* buffer);

    // From QThread
    virtual void run();

private:
    GE::AudioMixer m_audioMixer;
    QMap<QString, GE::AudioBuffer*> m_samples;

#ifndef PULSE
    GE::AudioOut* m_audioOut;
#endif

#ifdef Q_OS_SYMBIAN
    QTimer m_audioPullTimer; // Used to tick the audio engine
#endif
};

#endif // SAMPLEPLAYER_H
