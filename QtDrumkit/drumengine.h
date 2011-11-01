#ifndef DRUMENGINE_H
#define DRUMENGINE_H

#include <QObject>
#include <QVariant>
#include <QPair>
#include <QTime>
#include <QTimer>

class SamplePlayer;

// This class provides DrumEngine with QML bindings.
// It has a state that can be queried with properties.
// It can play samples, record a drum track, and start
// and stop playback.
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
    // Play a sample with a name.
    Q_INVOKABLE void playSample(QString name);

    // Start playback.
    Q_INVOKABLE void play();

    // Start recording.
    Q_INVOKABLE void record();

    // Stop playback or recording.
    Q_INVOKABLE void stop();

    // Set volume, range 0..10.
    Q_INVOKABLE void setVolume(int value);

public:
    // Checks whether playback is possible.
    bool canPlay() const;

    // Checks whether recording is possible.
    bool canRecord() const;

    // Checks if playback is in progress.
    bool isPlaying() const;

    // Checks if recording is in progress.
    bool isRecording() const;

private slots:
    // Timer event used for playback.
    void playbackTimerEvent();

private:
    // Emits state update signals.
    void updateState();

    enum {
        StateStop = 0,
        StatePlayback,
        StateRecord
    } m_state;

    // Drum track is stored in this list as pairs of time stamp and sample name.
    QList<QPair<QTime, QString> > m_drumTrack;

    // Start time of recording is stored as a reference.
    QTime m_drumTrackStartTime;

    // Timer used for playback.
    QTimer m_playbackTimer;

    // Starting time of the playback. This is used to determine
    // when to advance to next playback position.
    QTime m_playbackStartTime;

    // Position in m_drumTrack when doing playback.
    int m_playbackPosition;

    // Sample player utility.
    SamplePlayer* m_samplePlayer;
};

#endif // DRUMENGINE_H
