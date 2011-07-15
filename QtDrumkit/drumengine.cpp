#include <QtCore/QDebug>
#include <QStringList>
#include "drumengine.h"

using namespace GE;

DrumEngine::DrumEngine(QObject *parent) 
    : QObject(parent),
      m_state(StateStop)
{

    m_audioMixer = new AudioMixer(this);
    m_audioOut = new AudioOut(m_audioMixer, this);

    //     m_audioMixer->setAbsoluteVolume(3.0f / m_players.size());

    m_audioMixer->setAbsoluteVolume(3.0f / 10);
    QStringList samples;
    samples << "cowbell" << "crash" << "hihat1" << "hihat2" 
	    << "kick" << "ride1" << "ride2" << "snare" 
	    << "splash" << "tom1" << "tom2" << "tom3";
    initSamples(samples);
}


DrumEngine::~DrumEngine()
{
}

void DrumEngine::initSamples(QStringList names) {
    foreach(QString name, names) {
	AudioBuffer* buffer = AudioBuffer::loadWav(":/samples/"+name+".wav", this);
	m_samples[name] = buffer;
    }
}

void DrumEngine::play(AudioBuffer* buffer) {
    AudioBufferPlayInstance* inst = buffer->playWithMixer(*m_audioMixer);
    if(inst) {
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
    qDebug() << "playSample" << name;
    play(m_samples[name]);
}

void DrumEngine::play()
{
    qDebug() << __PRETTY_FUNCTION__;
    m_state = StatePlayback;
    updateState();
}

void DrumEngine::record()

{
    qDebug() << __PRETTY_FUNCTION__;
    m_state = StateRecord;
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
    qDebug() << __PRETTY_FUNCTION__;
    m_state = StateStop;
    updateState();
}

bool DrumEngine::isPlaying() 
{
    qDebug() << __PRETTY_FUNCTION__;
    return m_state == StatePlayback;
}

bool DrumEngine::isRecording() 
{
    qDebug() << __PRETTY_FUNCTION__;
    return m_state == StateRecord;
}

bool DrumEngine::canPlay() 
{
    qDebug() << __PRETTY_FUNCTION__;
    return false;
}

bool DrumEngine::canRecord() 
{
    qDebug() << __PRETTY_FUNCTION__;
    return m_state == StateStop || m_state == StateRecord;
}
