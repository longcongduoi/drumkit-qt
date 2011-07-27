# Add more folders to ship with the application, here

common_qml.source = qml/common
common_qml.target = qml

symbian {
   platform_qml.source = qml/symbian
   platform_qml.target = qml
   QML_IMPORT_PATH = qml/symbian
} else {
   platform_qml.source = qml/harmattan
   platform_qml.target = qml
   QML_IMPORT_PATH = qml/harmattan
}

DEPLOYMENTFOLDERS = platform_qml common_qml

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH = qml/common

symbian:TARGET.UID3 = 0xE19608FC

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
  CONFIG += maemo6
}

unix:!symbian {
   maemo5 {
      error(Maemo5 not supported)
   } 

   maemo6 {
     message(Harmattan)
     DEFINES += Q_WS_MAEMO_6
   } else {
     message(Desktop)
   }

   CONFIG += link_pkgconfig
   PKGCONFIG += libpulse
   DEFINES += PULSE

   SOURCES += audiooutpulse.cpp
   HEADERS += audiooutpulse.h
}

symbian {
   message(Symbian)
}

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp 
SOURCES += drumengine.cpp
SOURCES += sampleplayer.cpp
HEADERS += drumengine.h
HEADERS += sampleplayer.h

RESOURCES += samples.qrc

INCLUDEPATH += QtGameEnabler/src
include(QtGameEnabler/qtgameenabler.pri)

# Put generated temp-files under tmp
MOC_DIR = tmp
OBJECTS_DIR = tmp
RCC_DIR = tmp
UI_DIR = tmp


# Please do not modify the following two lines. Required for deployment.
include(qmlapplicationviewer/qmlapplicationviewer.pri)
qtcAddDeployment()

OTHER_FILES += \
    qtc_packaging/debian_harmattan/rules \
    qtc_packaging/debian_harmattan/README \
    qtc_packaging/debian_harmattan/copyright \
    qtc_packaging/debian_harmattan/control \
    qtc_packaging/debian_harmattan/compat \
    qtc_packaging/debian_harmattan/changelog
