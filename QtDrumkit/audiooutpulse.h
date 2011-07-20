#ifndef AUDIOOUTPULSE_H
#define AUDIOOUTPULSE_H

#include "GEAudioOut.h"

// Initialize Pulse Audio output. 
// Blocks until pulseOutDeinit() has been called.
// Returns 0 on success.
int pulseOutInitialize(GE::AudioSource* audioSource);

// Deinitialize Pulse Audio output.
void pulseOutDeinit();

#endif
