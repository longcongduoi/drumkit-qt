#include <QtCore/QDebug>
#include <QStringList>
#include "sampleplayer.h"

using namespace GE;

SamplePlayer::SamplePlayer(QObject *parent) 
    : QObject(parent)
{
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


SamplePlayer::~SamplePlayer()
{
#ifdef Q_OS_SYMBIAN
    m_audioPullTimer.stop();
#endif
}

void SamplePlayer::play(AudioBuffer* buffer) 
{
    Q_ASSERT(buffer);
    AudioBufferPlayInstance* inst = buffer->playWithMixer(m_audioMixer);   
    if(inst == 0) {
        qWarning() << "playWithMixer failed";
    }
}

void SamplePlayer::playSample(QString name)
{
    play(m_samples[name]);
}

