#include <QtCore/QDebug>
#include <stdio.h>
#include <pulse/pulseaudio.h>

#include "audiopulseaudio.h"
#include "audiosourceif.h"

// This code is largely based on SampleAsyncPlayback example
// http://www.pulseaudio.org/wiki/SampleAsyncPlayback

using namespace GE;

static int latency = 20000; // start latency in micro seconds
static pa_buffer_attr bufattr;
static pa_sample_spec ss;
static short* buffer;
static int bufferSize;
static bool exitFlag = false;

// This callback gets called when our context changes state.  We really only
// care about when it's ready or if it has failed
static void pa_state_cb(pa_context *c, void *userdata) {
    pa_context_state_t state;
    int *pa_ready = (int*)userdata;
    state = pa_context_get_state(c);
    switch  (state) {
        // These are just here for reference
        case PA_CONTEXT_UNCONNECTED:
        case PA_CONTEXT_CONNECTING:
        case PA_CONTEXT_AUTHORIZING:
        case PA_CONTEXT_SETTING_NAME:
        default:
            break;
        case PA_CONTEXT_FAILED:
        case PA_CONTEXT_TERMINATED:
            *pa_ready = 2;
            break;
        case PA_CONTEXT_READY:
            *pa_ready = 1;
            break;
    }
}

// This callback is called when more data is required for playback.
// Data is retrieved from GE::AudioSource, which is the mixer.
static void stream_request_cb(pa_stream *s, size_t length, void *userdata) {

    AudioSource* source = reinterpret_cast<AudioSource*>(userdata);
    if (bufferSize < length*sizeof(short)) {
        bufferSize = length*sizeof(short)*2;
        buffer = (short*) malloc(bufferSize*sizeof(short));
    }
    memset(buffer, 0, length*sizeof(short));
    source->pullAudio(buffer, length/2);

    // Write all the requested bytes. If sample has ended, the
    // rest are empty bytes.
    pa_stream_write(s, buffer, length, NULL, 0LL, PA_SEEK_RELATIVE);
}

// Initializes Pulse Audio and starts the mainloop.
int pulseOutInitialize(AudioSource* audioSource) {
    pa_mainloop *pa_ml;
    pa_mainloop_api *pa_mlapi;
    pa_context *pa_ctx;
    pa_stream *playstream;
    int r;
    int pa_ready = 0;
    int retval = -1;
    exitFlag = false;

    bufferSize = 8192; // initial buffer size
    buffer = (short*) malloc(bufferSize*sizeof(short));

    // Create a mainloop API and connection to the default server
    pa_ml = pa_mainloop_new();
    pa_mlapi = pa_mainloop_get_api(pa_ml);
    pa_ctx = pa_context_new(pa_mlapi, "QtDrumkit");
    pa_context_connect(pa_ctx, NULL, (pa_context_flags_t)0, NULL);

    // This function defines a callback so the server will tell us it's state.
    // Our callback will wait for the state to be ready.  The callback will
    // modify the variable to 1 so we know when we have a connection and it's
    // ready.
    // If there's an error, the callback will set pa_ready to 2
    pa_context_set_state_callback(pa_ctx, pa_state_cb, &pa_ready);

    // We can't do anything until PA is ready, so just iterate the mainloop
    // and continue
    while (pa_ready == 0) {
        pa_mainloop_iterate(pa_ml, 1, NULL);
    }
    if (pa_ready == 2) {
        goto exit;
    }

    // Sample format:
    ss.rate = 22050;
    ss.channels = 2;
    ss.format = PA_SAMPLE_S16LE;

    playstream = pa_stream_new(pa_ctx, "Playback", &ss, NULL);
    if (!playstream) {
        printf("pa_stream_new failed\n");
        goto exit;
    }

    pa_stream_set_write_callback(playstream, stream_request_cb, audioSource);
    bufattr.fragsize = (uint32_t)-1;
    bufattr.maxlength = pa_usec_to_bytes(latency,&ss);
    bufattr.minreq = pa_usec_to_bytes(0,&ss);
    bufattr.prebuf = (uint32_t)-1;
    bufattr.tlength = pa_usec_to_bytes(latency,&ss);
    r = pa_stream_connect_playback(
        playstream,
        NULL,
        &bufattr,
        pa_stream_flags_t(PA_STREAM_INTERPOLATE_TIMING | PA_STREAM_ADJUST_LATENCY | PA_STREAM_AUTO_TIMING_UPDATE),
        NULL,
        NULL);

    if (r < 0) {
        printf("pa_stream_connect_playback failed\n");
        goto exit;
    }

    retval = 0; // everything ok

    // Iterate the main loop until exit flag is set.
    while (!exitFlag) {
        pa_mainloop_iterate(pa_ml, 1, NULL);
    }

exit:
    // clean up and disconnect
    pa_context_disconnect(pa_ctx);
    pa_context_unref(pa_ctx);
    pa_mainloop_free(pa_ml);
    free(buffer);
    return retval;
}

// Deinitialize by setting the flag that stops the mainloop.
void pulseOutDeinit() {
    exitFlag = true;
}


/*!
 * \class AudioPulseAudio
 * \brief Audio output using PulseAudio, Linux desktop/Harmattan only.
 */

AudioPulseAudio::AudioPulseAudio(GE::AudioMixer& audioMixer, QObject *parent) 
    : QThread(parent),
      m_audioMixer(audioMixer)
{
    // Start pulse audio thread.
    start();
    qDebug() << "Pulse Audio initialized";
}

AudioPulseAudio::~AudioPulseAudio()
{
    // Stop Pulse Audio wait for the thread to exit.
    pulseOutDeinit();
    wait();
    qDebug() << "Pulse Audio deinitialized";
}

void AudioPulseAudio::run()
{
    // The thread initializes Pulse Audio and sits in a loop processing
    // audio.
    pulseOutInitialize(&m_audioMixer);
}


