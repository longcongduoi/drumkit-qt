# Copyright (c) 2011 Nokia Corporation.

CONFIG += release
QT += opengl

# Add more folders to ship with the application, here
common_qml.source = qml/common
common_qml.target = qml

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH += qml/common

VERSION = 1.0

# Smart Installer package's UID
# This UID is from the protected range and therefore the package will
# fail to install if self-signed. By default qmake uses the unprotected
# range value if unprotected UID is defined for the application and
# 0x2002CCCF value if protected UID is given to the application
#symbian:DEPLOYMENT.installer_header = 0x2002CCCF

# Allow network access on Symbian
#symbian:TARGET.CAPABILITY += NetworkServices

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

# Harmattan check trickery
exists($$QMAKE_INCDIR_QT"/../qmsystem2/qmkeys.h"):!contains(MEEGO_EDITION,harmattan): {
  MEEGO_VERSION_MAJOR     = 1
  MEEGO_VERSION_MINOR     = 2
  MEEGO_VERSION_PATCH     = 0
  MEEGO_EDITION           = harmattan
  DEFINES += MEEGO_EDITION_HARMATTAN
  CONFIG += harmattan
}

unix:!symbian {
   maemo5 {
      error(Maemo5 not supported)
   } 
   harmattan {
     DEFINES += Q_WS_MAEMO_6
     message(Harmattan)
   } else {
     message(Desktop)
   }
}

symbian {
   message(Symbian)
   ICON = QtDrumkit.svg
   TARGET.UID3 = 0xE19608FC
   DEFINES += USE_DEVSOUND

   platform_qml.source = qml/symbian
   platform_qml.target = qml
   QML_IMPORT_PATH += qml/symbian

   SOURCES += audiogameenabler.cpp
   HEADERS += audiogameenabler.h

   SOURCES += audiodevsound.cpp
   HEADERS += audiodevsound.h

   SOURCES += volumekeys.cpp
   HEADERS += volumekeys.h

   LIBS += -lremconcoreapi -lremconinterfacebase
   INCLUDEPATH += /epoc32/include/mw

   LIBS += -lmmfdevsound
}

unix|harmattan:!symbian {

   # Use Pulse Audio on Linux
   CONFIG += link_pkgconfig
   PKGCONFIG += libpulse
   DEFINES += USE_PULSEAUDIO
   #DEFINES += USE_GAMEENABLER

   platform_qml.source = qml/harmattan
   platform_qml.target = qml
   QML_IMPORT_PATH += qml/harmattan

   SOURCES += audiogameenabler.cpp
   HEADERS += audiogameenabler.h

   SOURCES += audiopulseaudio.cpp
   HEADERS += audiopulseaudio.h
}

# The following is needed for the volume buttons to work.
harmattan {
   gameclassify.files += qtc_packaging/debian_harmattan/QtDrumkit.conf
   gameclassify.path = /usr/share/policy/etc/syspart.conf.d
   INSTALLS += gameclassify
}


SOURCES += main.cpp \
    qmlviewer.cpp \
    touchevents.cpp
SOURCES += drumengine.cpp
SOURCES += sampleplayer.cpp
HEADERS += drumengine.h \
    qmlviewer.h \
    touchevents.h
HEADERS += audiointerface.h
HEADERS += sampleplayer.h

RESOURCES += samples.qrc

INCLUDEPATH += QtGameEnabler/src
include(QtGameEnabler/qtgameenabler.pri)

# Put generated temp-files under tmp
MOC_DIR = tmp
OBJECTS_DIR = tmp
RCC_DIR = tmp
UI_DIR = tmp

DEPLOYMENTFOLDERS = platform_qml common_qml

# Please do not modify the following two lines. Required for deployment.
include(qmlapplicationviewer/qmlapplicationviewer.pri)
qtcAddDeployment()

OTHER_FILES += \
    qtc_packaging/debian_harmattan/rules \
    qtc_packaging/debian_harmattan/README \
    qtc_packaging/debian_harmattan/copyright \
    qtc_packaging/debian_harmattan/control \
    qtc_packaging/debian_harmattan/compat \
    qtc_packaging/debian_harmattan/changelog \
    qtc_packaging/debian_harmattan/QtDrumkit.conf
