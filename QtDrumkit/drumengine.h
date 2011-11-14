/**
 * Copyright (c) 2011 Nokia Corporation.
 * All rights reserved.
 *
 * Part of the QtDrumkit
 *
 * For the applicable distribution terms see the license text file included in
 * the distribution.
 */

#ifndef DRUMENGINE_H
#define DRUMENGINE_H

#include <QObject>
#include <QVariant>
#include <QPair>
#include <QTime>
#include <QTimer>

class SamplePlayer;

/*!
  \class DrumEngine
  \brief This class provides DrumEngine with QML bindings.
         It has a state that can be queried with properties.
         It can play samples, record a drum track, and start
         and stop playback.
*/
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
    void playSample(QString name);
    void play();
    void record();
    void stop();

public:
    bool canPlay() const;
    bool canRecord() const;
    bool isPlaying() const;
    bool isRecording() const;

private slots:
    void playbackTimerEvent();

private:
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
    SamplePlayer *m_samplePlayer;
};

#endif // DRUMENGINE_H
