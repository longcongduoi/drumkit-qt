/**
 * Copyright (c) 2011 Nokia Corporation.
 * All rights reserved.
 *
 * Part of the QtDrumkit
 *
 * For the applicable distribution terms see the license text file included in
 * the distribution.
 */

#include <QtCore/QDebug>
#include "drumengine.h"
#include "sampleplayer.h"

using namespace GE;

DrumEngine::DrumEngine(QObject *parent) 
    : QObject(parent),
      m_state(StateStop)
{
    connect(&m_playbackTimer, SIGNAL(timeout()),
	    this, SLOT(playbackTimerEvent()));

    m_samplePlayer = new SamplePlayer(this);
}

DrumEngine::~DrumEngine()
{
}

void DrumEngine::playSample(QString name)
{
    m_samplePlayer->playSample(name);

    // If recording, store this sample to drum track.
    if (m_state == StateRecord) {
	m_drumTrack.append(qMakePair(QTime::currentTime(), name));

        // In case of the first note, the start time gets updated.
        if (m_drumTrackStartTime.isNull()) {
	    m_drumTrackStartTime = QTime::currentTime();
	}
    }
}

void DrumEngine::play()
{
    m_state = StatePlayback;  
    updateState();

    // Start playback from position 0 using a timer.
    m_playbackStartTime = QTime::currentTime();
    m_playbackPosition = 0;
    m_playbackTimer.start(10); // 10 ms interval
}

void DrumEngine::record()
{
    m_state = StateRecord;
    updateState();

    // Clear the old drumtrack before recording.
    m_drumTrack.clear();
    m_drumTrackStartTime = QTime();
}

void DrumEngine::updateState()
{
    // Signal state changes.
    emit canRecordChanged();
    emit canPlayChanged();
    emit isPlayingChanged();
    emit isRecordingChanged();
}

void DrumEngine::stop()
{
    m_state = StateStop;
    updateState();

    m_playbackTimer.stop();
}

bool DrumEngine::isPlaying() const
{
    return m_state == StatePlayback;
}

bool DrumEngine::isRecording() const
{
    return m_state == StateRecord;
}

bool DrumEngine::canPlay() const
{
    // Requirement for playback.
    return m_drumTrack.size() > 0;
}

bool DrumEngine::canRecord() const
{
    return m_state == StateStop || m_state == StateRecord;
}

void DrumEngine::playbackTimerEvent()
{
    // Figure out when the current note should be played
    // using playback start time and the drum track start time.
    // Then play the note and advance to the next position,
    // or stop playback if the end was reached.

    int elapsed = m_playbackStartTime.msecsTo(QTime::currentTime());
    QPair<QTime, QString> note = m_drumTrack[m_playbackPosition];
    int noteStart = m_drumTrackStartTime.msecsTo(note.first);
    if (elapsed >= noteStart) {
	playSample(note.second);
	m_playbackPosition++;

        if (m_playbackPosition >= m_drumTrack.size()) {
	    stop();
	}
    }
}
