#include <QDebug>
#include <QtGui/QApplication>
#include <QGLWidget>
#include <QtDeclarative>

#include "qmlapplicationviewer.h"
#include "drumengine.h"



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<DrumEngine>("DrumEngine", 1,0, "DrumEngine");

    QmlApplicationViewer viewer;
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationLockLandscape);
    //viewer.setMainQmlFile(QLatin1String("qml/QtDrumkit/main.qml"));
#ifdef Q_OS_SYMBIAN
    viewer.setMainQmlFile(QLatin1String("qml/symbian/main.qml"));
#else
    viewer.setMainQmlFile(QLatin1String("qml/harmattan/main.qml"));
#endif


// #if defined(Q_WS_MAEMO_5) || defined(Q_OS_SYMBIAN) || defined(Q_WS_HARMATTAN)
//     // Mobile screen dimensions
//     QDesktopWidget *desktop = QApplication::desktop();
//     const QRect screenRect = desktop->screenGeometry();
// #else
//     // Desktop defaults
//     QPoint topLeft(100,100);
//     QSize size(854, 480);
//     QRect screenRect(topLeft, size);
// #endif
//     // Set the screen size to QML context
//     QDeclarativeContext* context = viewer.rootContext();
//     context->setContextProperty("screenWidth", screenRect.width());
//     context->setContextProperty("screenHeight", screenRect.height());

    // For N900 and Harmattan set OpenGL rendering
#if defined(Q_WS_MAEMO_5) || defined(Q_WS_MAEMO_6)
    QGLFormat fmt = QGLFormat::defaultFormat();
    fmt.setDirectRendering(true);
    fmt.setDoubleBuffer(true);

    QGLWidget *glWidget = new QGLWidget(fmt);
    viewer.setViewport(glWidget);
#endif

#if defined(Q_WS_MAEMO_6) || defined(Q_OS_SYMBIAN)
    viewer.showFullScreen();
//    viewer.show();
#else
    viewer.show();
#endif

    return app.exec();
}
