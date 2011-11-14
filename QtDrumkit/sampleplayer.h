/**
 * Copyright (c) 2011 Nokia Corporation.
 * All rights reserved.
 *
 * Part of the QtDrumkit
 *
 * For the applicable distribution terms see the license text file included in
 * the distribution.
 */

#ifndef SAMPLEPLAYER_H
#define SAMPLEPLAYER_H

#include <QObject>
#include <QMap>

#include "audiointerface.h"
#include "audiomixer.h"
#include "audiobuffer.h"

#ifdef Q_OS_SYMBIAN
#include "volumekeys.h"
#endif

/*!
  \class SamplePlayer
  \brief A class for playing samples.
*/
class SamplePlayer : public QObject
{
    Q_OBJECT
public:
    explicit SamplePlayer(QObject *parent = 0);
    virtual ~SamplePlayer();

public slots:

/*!
  Plays a sample, where name is one of:
  cowbell, crash, hihat1, hihat2, kick, ride1, ride2, snare,
  splash, tom1, tom2, tom3, china.
*/
    void playSample(QString name);

private slots:

    void volumeUp();
    void volumeDown();

private:
    void play(GE::AudioBuffer *buffer);

    // Map of preloaded sample data.
    QMap<QString, GE::AudioBuffer*> m_samples;
    
    // Mixer audio source
    GE::AudioMixer m_audioMixer;

    // Interface to the audio output backend.
    AudioInterface *m_audioIf;

#ifdef Q_OS_SYMBIAN
    VolumeKeys *m_volumeKeys;
#endif
};

#endif // SAMPLEPLAYER_H
