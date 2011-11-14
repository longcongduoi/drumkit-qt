/**
 * Copyright (c) 2011 Nokia Corporation.
 * All rights reserved.
 *
 * Part of the QtDrumkit
 *
 * For the applicable distribution terms see the license text file included in
 * the distribution.
 */

#ifndef AUDIO_DEVSOUND_H
#define AUDIO_DEVSOUND_H

#include <QObject>
#include <QTimer>
#include <mmf/server/sounddevice.h>

#include "audiointerface.h"
#include "audioout.h"
#include "audiomixer.h"

/*!
 * \class AudioDevSound
 * \brief Audio output using Symbian native CMMFDevSound.
 */
class AudioDevSound : public QObject,
                      public MDevSoundObserver,
                      public AudioInterface
{
    Q_OBJECT
public:
    explicit AudioDevSound(GE::AudioMixer &audioMixer, QObject *parent = 0);
    virtual ~AudioDevSound();

public: // From MDevSoundObserver

   void InitializeComplete(TInt aError);
   void ToneFinished(TInt aError);
   void BufferToBeFilled(CMMFBuffer* aBuffer);
   void PlayError(TInt aError);
   void BufferToBeEmptied(CMMFBuffer *aBuffer);
   void RecordError(TInt aError);
   void ConvertError(TInt aError);
   void DeviceMessage(TUid aMessageType, const TDesC8 &aMsg);

public: // From AudioInterface

   void volumeUp();
   void volumeDown();

private:
    GE::AudioMixer &m_audioMixer;
    CMMFDevSound *m_devSound;
};

#endif 
