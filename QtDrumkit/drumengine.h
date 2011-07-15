#ifndef DRUMENGINE_H
#define DRUMENGINE_H

#include <QObject>
#include <QTimer>

#include "GEAudioOut.h"
#include "GEAudioMixer.h"
#include "GEAudioBuffer.h"
#include "GEAudioBufferPlayInstance.h"

class DrumEngine : public QObject
{
    Q_OBJECT
public:
    explicit DrumEngine(QObject *parent = 0);
    virtual ~DrumEngine();

public slots:
    void playCowbell();
    void playCrash();
    void playHihat1();
    void playHihat2();
    void playKick();
    void playRide1();
    void playRide2();
    void playSnare();
    void playSplash();
    void playTom1();
    void playTom2();
    void playTom3();
private slots:

private:
    void play(GE::AudioBuffer* buffer);

    GE::AudioOut* m_audioOut;
    GE::AudioMixer m_audioMixer;
    QList<GE::AudioBufferPlayInstance*> m_players;
    GE::AudioBuffer* m_cowbell;
    GE::AudioBuffer* m_crash;
    GE::AudioBuffer* m_hihat1;
    GE::AudioBuffer* m_hihat2;
    GE::AudioBuffer* m_kick;
    GE::AudioBuffer* m_ride1;
    GE::AudioBuffer* m_ride2;
    GE::AudioBuffer* m_snare;
    GE::AudioBuffer* m_splash;
    GE::AudioBuffer* m_tom1;
    GE::AudioBuffer* m_tom2;
    GE::AudioBuffer* m_tom3;

#ifdef Q_OS_SYMBIAN
    QTimer m_audioPullTimer; // Used to tick the audio engine
#endif
};

#endif // DRUMENGINE_H
