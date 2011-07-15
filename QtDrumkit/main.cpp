#include <QDebug>
#include <QtGui/QApplication>
#include <QDeclarativeContext>
#include "qmlapplicationviewer.h"
#include "drumengine.h"


#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QGraphicsView>

class Item : public QGraphicsItem
{
public:
    Item(DrumEngine& engine) : e(engine) {}

    QRectF boundingRect() const
    {
	qreal penWidth = 1;
	return QRectF(-100 - penWidth / 2, -100 - penWidth / 2,
		      200 + penWidth, 200 + penWidth);
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
	       QWidget *widget)
    {
	painter->drawRoundedRect(-100, -100, 200, 200, 5, 5);
    }


    void mousePressEvent(QGraphicsSceneMouseEvent * event ) {
	e.playSnare();
	event->ignore();
	qDebug() << "mousePress";
    }

    void keyPressEvent(QKeyEvent * event ) {
	e.playCowbell();
	qDebug() << "keyPress";
    }
    DrumEngine& e;
};


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    DrumEngine drumEngine;

    QmlApplicationViewer viewer;
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationLockLandscape);
    viewer.setMainQmlFile(QLatin1String("qml/QtDrumkit/main.qml"));
    QDeclarativeContext* ctx = viewer.rootContext();
    ctx->setContextProperty("DrumEngine", &drumEngine);

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
#if defined(Q_WS_MAEMO_5) || defined(Q_WS_HARMATTAN)
    QGLFormat fmt = QGLFormat::defaultFormat();
    fmt.setDirectRendering(true);
    fmt.setDoubleBuffer(true);

    QGLWidget *glWidget = new QGLWidget(fmt);
    viewer.setViewport(glWidget);
#endif

    viewer.showExpanded();



//     QGraphicsScene scene;
//     scene.setSceneRect( -100.0, -100.0, 200.0, 200.0 );
//     Item* i = new Item(drumEngine);
//     i->setFlags( QGraphicsItem::ItemIsFocusable );
//     i->setX(0);
//     i->setY(0);
//     scene.addItem(i);
//     i->grabKeyboard();
//     QGraphicsView view( &scene );
//     view.showFullScreen();

    return app.exec();
}
