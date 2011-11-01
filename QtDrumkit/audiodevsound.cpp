#include <QtCore/QDebug>

#include "audiodevsound.h"

#include "GEAudioMixer.h"
#include "GEAudioBuffer.h"
#include "GEAudioBufferPlayInstance.h"

AudioDevSound::AudioDevSound(GE::AudioMixer& audioMixer, QObject *parent)
    : QObject(parent),
      m_audioMixer(audioMixer)
{
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

    // Configure sample format.

    TMMFCapabilities caps = m_devSound->Config();
    caps.iChannels = EMMFStereo;
    caps.iEncoding = EMMFSoundEncoding16BitPCM;
    caps.iRate = EMMFSampleRate22050Hz;

    // Possible errors are ignored below:

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
    // The value here was found by experimenting on N8 and 701.
    // The lowest value to work on these devices is 420,
    // lower values cause distortion in the sound.
    // 512 is chosen to include some safety margin.
    const TInt reqSize = 512;

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
