#ifndef DRUMENGINE_H
#define DRUMENGINE_H

#include <QObject>
#include <QVariant>

#include "GEAudioOut.h"
#include "GEAudioMixer.h"
#include "GEAudioBuffer.h"
#include "GEAudioBufferPlayInstance.h"

class DrumEngine : public QObject
{
    Q_OBJECT
    public:
    explicit DrumEngine(QObject *parent = 0);
    virtual ~DrumEngine();

    Q_PROPERTY(bool canPlay
	       READ canPlay
	       NOTIFY canPlayChanged);

    Q_PROPERTY(bool canRecord
	       READ canRecord
	       NOTIFY canRecordChanged);

    Q_PROPERTY(bool isPlaying
	       READ isPlaying
	       NOTIFY isPlayingChanged);

    Q_PROPERTY(bool isRecording
	       READ isRecording
	       NOTIFY isRecordingChanged);
signals:
    void isPlayingChanged();
    void isRecordingChanged();
    void canPlayChanged();
    void canRecordChanged();

public slots:
    Q_INVOKABLE void playSample(QString name);

    Q_INVOKABLE void play();
    Q_INVOKABLE void record();
    Q_INVOKABLE void stop();

private:
    enum {
        StateStop = 0,
        StatePlayback,
        StateRecord
    } m_state;


public:
    bool canPlay();
    bool canRecord();
    bool isPlaying();
    bool isRecording();

private slots:

private:
    void play(GE::AudioBuffer* buffer);
    void initSamples(QStringList names);
    void updateState();

    GE::AudioOut* m_audioOut;
    GE::AudioMixer* m_audioMixer;
    QMap<QString, GE::AudioBuffer*> m_samples;
};

#endif // DRUMENGINE_H
