CONFIG += mobility
MOBILITY += multimedia

DEFINES -= GE_DEBUG

SOURCES += \
    $$PWD/src/GEAudioBuffer.cpp \
    $$PWD/src/GEAudioBufferPlayInstance.cpp \
    $$PWD/src/GEAudioMixer.cpp \
    $$PWD/src/GEAudioOut.cpp \
    $$PWD/src/GEInterfaces.cpp


HEADERS  += \
    $$PWD/src/GEAudioBuffer.h \
    $$PWD/src/GEAudioBufferPlayInstance.h \
    $$PWD/src/GEAudioMixer.h \
    $$PWD/src/GEAudioOut.h \
    $$PWD/src/GEInterfaces.h \
    $$PWD/src/trace.h \
