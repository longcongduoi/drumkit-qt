/**
 * Copyright (c) 2011 Nokia Corporation.
 * All rights reserved.
 *
 * Part of the QtDrumkit
 *
 * For the applicable distribution terms see the license text file included in
 * the distribution.
 */

#include <QDebug>
#include <QtGui/QApplication>
#include <QGLWidget>
#include <QtDeclarative>

#include "qmlapplicationviewer.h"
#include "drumengine.h"
#include "qmlviewer.h"
#include "touchevents.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Register QML bindings fo DrumEngine and TouchEvents
    qmlRegisterType<DrumEngine>("DrumEngine", 1,0, "DrumEngine");
    qmlRegisterType<TouchEvents>("TouchEvents", 1,0, "TouchEvents");

    QmlViewer viewer;
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationLockLandscape);

    // Check for VGA resolution and inform QML. Needed for some
    // gfx layouting on on Symbian devices with VGA resolution (E6).
    QDesktopWidget *desktop = QApplication::desktop();
    const QRect screenRect = desktop->screenGeometry();
    if (screenRect.width() == 640 && screenRect.height() == 480) {
        viewer.rootContext()->setContextProperty("screenVGA", true);
    } else {
        viewer.rootContext()->setContextProperty("screenVGA", false);
    }

    // Select the main.qml according to platform.
#ifdef Q_OS_SYMBIAN
    viewer.setMainQmlFile(QLatin1String("qml/symbian/main.qml"));
#else
    viewer.setMainQmlFile(QLatin1String("qml/harmattan/main.qml"));
#endif

    // Enable OpenGL rendering
    QGLFormat fmt = QGLFormat::defaultFormat();
    fmt.setDirectRendering(true);
    fmt.setDoubleBuffer(true);
    QGLWidget *glWidget = new QGLWidget(fmt);
    viewer.setViewport(glWidget);
    viewer.showFullScreen();

    return app.exec();
}

