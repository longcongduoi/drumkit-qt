Qt Drumkit is a virtual drumkit which lets you play percussion sounds by tapping the screen.

The Qt Drumkit application contains two views for playing:

 * simple view with 2D pads
 * 3D drumkit view

You can record your beats and play them back later. It is also possible to play on top of your last recording.

The user interface is implemented with QML. The sound engine and playback logic is C++, which is accessed from QML UI. For audio playback the application uses a combination of [https://projects.developer.nokia.com/qtgameenabler/wiki Qt GameEnabler], [http://library.developer.nokia.com/topic/GUID-E35887BB-7E58-438C-AA27-97B2CDE7E069/GUID-251A35C1-CC66-4DE4-9EBE-964026E89E7F/GUID-B3E9B015-1413-35A6-A316-D1C01C1001AD.html?resultof=%22%43%4d%4d%46%44%65%76%53%6f%75%6e%64%22%20%22%63%6d%6d%66%64%65%76%73%6f%75%6e%64%22%20 DevSound] (native Symbian library) and [https://www.pulseaudio.org/ PulseAudio] (native !MeeGo library). Read more about [http://projects.developer.nokia.com/QtDrumkit/wiki design and implementation] of the application.

The application has been ported from a corresponding [http://projects.developer.nokia.com/JMEDrumkit Java application]. In parallel with the Qt Quick application, an [http://projects.developer.nokia.com/wpdrumkit XNA version] has also been developed for Windows Phone. The implementations are compared in [http://projects.developer.nokia.com/QtDrumkit/wiki/Comparison this article]. 


[[Image(wiki:WikiStart:screen1_small.png)]]  [[Image(wiki:WikiStart:screen2_small.png)]]

Compatibility

 * Symbian S^3 or newer, Qt 4.7.4
 * !MeeGo 1.2 Harmattan

Tested on

 * Nokia N8
 * Nokia C7
 * Nokia E6
 * Nokia E7
 * Nokia 701
 * Nokia N9
 * Nokia N950

[[FeaturedDownloads()]]
