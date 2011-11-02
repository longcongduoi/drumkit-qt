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

#if defined(Q_WS_MAEMO_6) || defined(Q_OS_SYMBIAN)
    viewer.showFullScreen();
#else
    viewer.show();
#endif

    return app.exec();
}

