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

    output.SetLength(buf->RequestSize());
    short* ptr = (short*)(output.Ptr());
    Mem::FillZ(ptr, buf->RequestSize());
    m_audioMixer.pullAudio(ptr, buf->RequestSize()/2);
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

