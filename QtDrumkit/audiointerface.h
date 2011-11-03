#ifndef AUDIOINTERFACE_H
#define AUDIOINTERFACE_H

// Interface for the audio backends.
class AudioInterface {
public:
    virtual void volumeUp() {}
    virtual void volumeDown() {}
};

#endif // AUDIOINTERFACE_H
