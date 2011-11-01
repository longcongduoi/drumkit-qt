#include <QtCore/QDebug>

#include "audiodevsound.h"

#include "GEAudioOut.h"
#include "GEAudioMixer.h"
#include "GEAudioBuffer.h"
#include "GEAudioBufferPlayInstance.h"

AudioDevSound::AudioDevSound(GE::AudioMixer& audioMixer, QObject *parent)
    : QObject(parent),
      m_audioMixer(audioMixer)
{
    m_audioOut = new GE::AudioOut(&m_audioMixer, this);

    m_devSound = CMMFDevSound::NewL();
    m_devSound->InitializeL(*this, KMMFFourCCCodePCM16, EMMFStatePlaying);

    qDebug() << "DevSound Audio initialized";
}


AudioDevSound::~AudioDevSound()
{
    m_devSound->Stop();
    delete m_devSound;
    qDebug() << "DevSound Audio deinitialized";
}

void AudioDevSound::InitializeComplete(TInt aError)
{
    qDebug() << "InitializeComplete " << aError;
    TMMFCapabilities caps = m_devSound->Config();
    caps.iChannels = EMMFStereo;
    caps.iEncoding = EMMFSoundEncoding16BitPCM;
    caps.iRate = EMMFSampleRate22050Hz;
    TRAPD(err, m_devSound->SetConfigL(caps));
    qDebug() << "SetConfigL()" << err;

    TRAP(err, m_devSound->PlayInitL());
    qDebug() << "PlayInitL()" << err;
}

void AudioDevSound::ToneFinished(TInt aError) 
{
    Q_UNUSED(aError);
}

void AudioDevSound::BufferToBeFilled(CMMFBuffer* aBuffer) 
{
    CMMFDataBuffer* buf = static_cast<CMMFDataBuffer*>(aBuffer);
    TDes8& output = buf->Data();

    // The default buffer size is 4096.
    // To improve latency, only part of the requested bytes are passed to DevSound.
    // The value here was found by experimenting on N8 and 701,
    // lower values cause distortion in the sound.
    const TInt reqSize = 420; // ok

    output.SetLength(reqSize);
    short* ptr = (short*)(output.Ptr());
    Mem::FillZ(ptr, reqSize);
    m_audioMixer.pullAudio(ptr, reqSize/2);
    m_devSound->PlayData();
}

void AudioDevSound::PlayError(TInt aError) 
{
    qDebug() << "PlayError" << aError;
}

void AudioDevSound::BufferToBeEmptied(CMMFBuffer* aBuffer)
{
    Q_UNUSED(aBuffer);
}

void AudioDevSound::RecordError(TInt aError) 
{
    Q_UNUSED(aError);
}

void AudioDevSound::ConvertError(TInt aError) 
{
    Q_UNUSED(aError);
}

void AudioDevSound::DeviceMessage(TUid aMessageType, const TDesC8& aMsg) 
{
    Q_UNUSED(aMessageType);
    Q_UNUSED(aMsg);
}


void AudioDevSound::setVolume(int value)
{
    // Parameter value range is 0..10
    int newVolume = (m_devSound->MaxVolume() * value) / 10;
    m_devSound->SetVolume(newVolume);
}
