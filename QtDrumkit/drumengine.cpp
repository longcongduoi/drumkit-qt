#include <QtCore/QDebug>
#include <QStringList>
#include "drumengine.h"

using namespace GE;

DrumEngine::DrumEngine(QObject *parent) 
    : QObject(parent),
      m_state(StateStop)
{
    connect(&m_playbackTimer, SIGNAL(timeout()),
	    this, SLOT(playbackTimerEvent()));

    m_audioOut = new AudioOut(&m_audioMixer, this);

    m_audioMixer.setAbsoluteVolume(3.0f / 10);

    QStringList samples;
    samples << "cowbell" << "crash" << "hihat1" << "hihat2" 
	    << "kick" << "ride1" << "ride2" << "snare" 
	    << "splash" << "tom1" << "tom2" << "tom3";

    foreach(QString name, samples) {
        m_samples[name] = AudioBuffer::loadWav(":/samples/"+name+".wav", this);
    }

#ifdef Q_OS_SYMBIAN
    m_audioPullTimer.setInterval(5);
    connect(&m_audioPullTimer, SIGNAL(timeout()), m_audioOut, SLOT(tick()));
    m_audioPullTimer.start();
#endif
}


DrumEngine::~DrumEngine()
{
#ifdef Q_OS_SYMBIAN
    m_audioPullTimer.stop();
#endif
}

void DrumEngine::play(AudioBuffer* buffer) {
    AudioBufferPlayInstance* inst = buffer->playWithMixer(m_audioMixer);
    if(inst == 0) {
        qWarning() << "playWithMixer failed";
    }
    //qDebug() << "Mixer source count:" << m_audioMixer->audioSourceCount();

//     AudioBufferPlayInstance* player = 0;
//     int i = 0;
//     foreach(AudioBufferPlayInstance* p, m_players) {
// 	if(!p->isPlaying()) {
// 	    player = p;
// 	    break;
// 	}
// 	i++;
//     }
//     if(player) {
// 	player->playBuffer(buffer);
// 	qDebug() << "Player" << i;
//     } else {
// 	qDebug() << "No available players";
//     }
}

void DrumEngine::playSample(QString name)
{
    play(m_samples[name]);

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
