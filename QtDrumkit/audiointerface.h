/**
 * Copyright (c) 2011 Nokia Corporation.
 * All rights reserved.
 *
 * Part of the QtDrumkit
 *
 * For the applicable distribution terms see the license text file included in
 * the distribution.
 */

#ifndef AUDIOINTERFACE_H
#define AUDIOINTERFACE_H

/*!
 * \class AudioInterface
 * \brief Interface for the audio backends.
 */
class AudioInterface {
public:
    virtual void volumeUp() {}
    virtual void volumeDown() {}
};

#endif // AUDIOINTERFACE_H
