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

    if(m_state == StateRecord) {
	m_drumTrack.append(qMakePair(QTime::currentTime(), name));
	if(m_drumTrackStartTime.isNull()) {
	    m_drumTrackStartTime = QTime::currentTime();
	}
    }
    qDebug() << "playSample" << name;
}

void DrumEngine::play()
{
    m_state = StatePlayback;  
    updateState();

    m_playbackStartTime = QTime::currentTime();
    m_playbackPosition = 0;
    m_playbackTimer.start(10); // 10 ms interval

}

void DrumEngine::record()
{
    m_state = StateRecord;

    m_drumTrack.clear();
    m_drumTrackStartTime = QTime();

    updateState();
}

void DrumEngine::updateState() 
{
    emit canRecordChanged();
    emit canPlayChanged();
    emit isPlayingChanged();
    emit isRecordingChanged();
}

void DrumEngine::stop()
{
    m_state = StateStop;
    m_playbackTimer.stop();
    updateState();
}

bool DrumEngine::isPlaying() 
{
    return m_state == StatePlayback;
}

bool DrumEngine::isRecording() 
{
    return m_state == StateRecord;
}

bool DrumEngine::canPlay() 
{
    return m_drumTrack.size() > 0;
}

bool DrumEngine::canRecord() 
{
    return m_state == StateStop || m_state == StateRecord;
}

void DrumEngine::playbackTimerEvent()
{
    QTime current(QTime::currentTime());
    int elapsed = m_playbackStartTime.msecsTo(current);

    QPair<QTime, QString> note = m_drumTrack[m_playbackPosition];
    int noteStart = m_drumTrackStartTime.msecsTo(note.first);
    if(elapsed >= noteStart) {
	playSample(note.second);
	m_playbackPosition++;

	if(m_playbackPosition >= m_drumTrack.size()) {
	    stop();
	}
    }
}
