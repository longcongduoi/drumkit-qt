#ifndef AUDIOINTERFACE_H
#define AUDIOINTERFACE_H

// Interface for the audio backends. Currently only one method available.
class AudioInterface {
public:
    virtual void setVolume(int value) = 0;
};

#endif // AUDIOINTERFACE_H
