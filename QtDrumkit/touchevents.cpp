#include "touchevents.h"
#include "qmlviewer.h"

TouchEvents::TouchEvents(QObject* parent)
    : QObject(parent)
{
    // Reroute QmlViewer instance signal through this object.
    connect(QmlViewer::instance(), SIGNAL(touchEventReceived(int,int)),
            this, SIGNAL(touchEventReceived(int,int)));
}
