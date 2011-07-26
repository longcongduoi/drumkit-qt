#include <QDebug>
#include <QtGui/QApplication>
#include <QGLWidget>
#include <QtDeclarative>

#include "qmlapplicationviewer.h"
#include "drumengine.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // DrumEngine QML bindings
    qmlRegisterType<DrumEngine>("DrumEngine", 1,0, "DrumEngine");

    QmlApplicationViewer viewer;
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationLockLandscape);

#ifdef Q_OS_SYMBIAN
    viewer.setMainQmlFile(QLatin1String("qml/symbian/main.qml"));
#else
    viewer.setMainQmlFile(QLatin1String("qml/harmattan/main.qml"));
#endif

    // Enable OpenGL rendering
//#if defined(Q_WS_MAEMO_5) || defined(Q_WS_MAEMO_6)
    QGLFormat fmt = QGLFormat::defaultFormat();
    fmt.setDirectRendering(true);
    fmt.setDoubleBuffer(true);
    QGLWidget *glWidget = new QGLWidget(fmt);
    viewer.setViewport(glWidget);
//#endif

#if defined(Q_WS_MAEMO_6) || defined(Q_OS_SYMBIAN)
    viewer.showFullScreen();
#else
    viewer.show();
#endif

    return app.exec();
}
