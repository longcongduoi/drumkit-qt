#include <QTouchEvent>
#include <QDebug>

#include "qmlviewer.h"

QmlViewer* QmlViewer::m_instance;

QmlViewer::QmlViewer()
{
    // We'd like to have touch events.
    setAttribute(Qt::WA_AcceptTouchEvents);
    m_instance = this;
}

QmlViewer* QmlViewer::instance() {
    return m_instance;
}

bool QmlViewer::event(QEvent* event) {

    // Grab touch events and signal appropriately.

    if (event->type() == QEvent::TouchBegin || event->type() == QEvent::TouchUpdate) {
        QTouchEvent* te = static_cast<QTouchEvent*>(event);
        foreach (QTouchEvent::TouchPoint tp, te->touchPoints()) {
            if (tp.state() == Qt::TouchPointPressed) {
                emit touchEventReceived(tp.screenPos().x(), tp.screenPos().y());
            }
        }
        return true;
    }
    return QmlApplicationViewer::event(event);
}

