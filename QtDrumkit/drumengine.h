#ifndef DRUMENGINE_H
#define DRUMENGINE_H

#include <QObject>
#include <QVariant>
#include <QPair>
#include <QTime>
#include <QTimer>

class SamplePlayer;

class DrumEngine : public QObject
{
    Q_OBJECT
    public:
    explicit DrumEngine(QObject *parent = 0);
    virtual ~DrumEngine();

    Q_PROPERTY(bool canPlay READ canPlay NOTIFY canPlayChanged);
    Q_PROPERTY(bool canRecord READ canRecord NOTIFY canRecordChanged);
    Q_PROPERTY(bool isPlaying READ isPlaying NOTIFY isPlayingChanged);
    Q_PROPERTY(bool isRecording READ isRecording NOTIFY isRecordingChanged);
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
    void playbackTimerEvent();

private:
    void updateState();

    QList<QPair<QTime, QString> > m_drumTrack;
    QTime m_drumTrackStartTime;

    QTimer m_playbackTimer;
    QTime m_playbackStartTime;
    int m_playbackPosition;

    SamplePlayer* m_samplePlayer;
};

#endif // DRUMENGINE_H
