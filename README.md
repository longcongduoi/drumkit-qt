Drumkit
=======

Drumkit is a virtual drumkit that lets you play percussion sounds
by tapping the screen.   

The application contains two views for playing, a simple view with 2D
pads and a 3D drumkit view. You can record your beats and play them
back afterwards. It is also possible to play on top of your last
recording.  

The user interface has been implemented with QML. The sound engine and
playback logic is C++, which is accessed from QML. For audio playback
the application uses a combination of  Qt GameEnabler,  DevSound
(native Symbian library), and  PulseAudio (native MeeGo library). 

The application has been ported from MIDP: Java Drumkit Example, available at  http://www.developer.nokia.com/info/sw.nokia.com/id/1fe81968-abbf-48d1-a137-a203094611b2/MIDP_Java_Drumkit_Example_v1_0_en.zip.html. At the same time, also an XNA version has been developed for Windows Phone, available at http://www.developer.nokia.com/info/sw.nokia.com/id/24a1d1e7-85cd-43ba-9382-260285144383/Drumkit_XNA.html.

This project is hosted in a GitHub:
https://github.com/nokia-developer/drumkit-qt

For more information about the implementation, see the project wiki page:
https://github.com/nokia-developer/drumkit-qt/wiki


PREREQUISITES
-------------------------------------------------------------------------------

- Qt and QML basics


IMPORTANT CLASSES / FILES
-------------------------------------------------------------------------------

- drumengine.h: Engine API visible to QML.
- sampleplayer.h: Handles initialisation of audio and playback of samples.
- qmlviewer.h: QmlApplicationViewer wrapper for catching touch events.
- touchevents.h: Touch event API visible to QML.

- Pads2d.qml: 2D pad view, positions Pad-components on the screen.
- Pads3d.qml: 3D drumkit view, positions Cymbal3d and Pad3d components
  on the screen.
- AnimButton.qml: A button component that is able to display an 
  animation using a PNG file. This is used for the record button.
- Button.qml: A simple button component that can be toggled. Used for
  all other buttons.
- Info.qml: A component displaying the information text.
- Pad.qml: Instrument pad component. Plays a specified sample when
  tapped and opens the instrument selector on a long tap.
- Pad3d.qml: Instrument pad component for the 3d view. Contains a
  bouncing animation in addition to the Pad component.
- Cymbal3d.qml: Cymbal pad component for the 3d view. Contains a
  rotation animation in addition to the Pad component.
- InstrumentSelector.qml: Instrument selector component. Arranges
  InstrumentButton components on a circle and performs transition
  animations. Used by the Pad component for configuring the sample for
  the pad.
- InstrumentButton.qml: A component for selecting instruments within the
  InstrumentSelector. Displays a selection highlight and plays the
  corresponding sample.

Important classes:

Qt:
- QDeclarativeView, QThread

Game Enabler:
- GE::AudioMixer
- GE::AudioBuffer

Symbian:
- CMMFDevSound
- MDevSoundObserver

Pulse Audio structs:
- pa_mainloop, pa_mainloop_api, pa_context, pa_stream

Standard QML elements used:
- Behavior
- Column
- Connections
- FocusScope
- Image 
- Item 
- MouseArea
- NumberAnimation
- PropertyAnimation
- SequentialAnimation
- Text
- Timer


PROJECT FOLDER STRUCTURE
-------------------------------------------------------------------------------

* main folder: C++ and project files
* qml/common: Common QML components for all platforms
* qml/harmattan: MeeGo/Harmattan-specific QML components
* qml/harmattan/gfx: MeeGo/Harmattan-specific graphics files
* qml/symbian: Symbian-specific QML components
* qml/symbian/gfx: Symbian-specific graphics files
* samples: Audio samples
* QtGameEnabler: QtGameEnabler audio-related source files.


BUILD & INSTALLATION INSTRUCTIONS
-------------------------------------------------------------------------------

**Preparations**

Check that you have the latest Qt/Qt SDK installed in the development
environment and on the device.

**Build & installation instructions using Qt SDK**

Compiling the examples;

1. Open the project file:
   File > Open File or Project, select QtDrumkit.pro.

2. Select target(s), for example Symbian^3, and press the Finish
   button.

3. Compile or deploy the project. 


COMPATIBILITY
-------------------------------------------------------------------------------

Symbian^3, Symbian Anna, Symbian Belle and MeeGo 1.2 Harmattan.

Tested on:
- Nokia N8 
- Nokia C7 
- Nokia E6
- Nokia E7
- Nokia 701 
- Nokia N9 
- Nokia N950

Developed with Qt SDK 1.1.


LICENSE AND COPYRIGHT INFORMATION
-------------------------------------------------------------------------------

Copyright (c) 2011-2013 Nokia Corporation.

See the license text file delivered with this project. The license file is 
also available online at:
https://github.com/nokia-developer/drumkit-qt/blob/master/Licence.txt



VERSION HISTORY 
-------------------------------------------------------------------------------

1.1     Updates to Drumkit description texts & updated the information view.
1.0     First version
