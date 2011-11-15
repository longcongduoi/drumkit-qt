/**
 * Copyright (c) 2011 Nokia Corporation.
 * All rights reserved.
 *
 * Part of the QtDrumkit
 *
 * For the applicable distribution terms see the license text file included in
 * the distribution.
 */

#include <QTouchEvent>
#include <QDebug>

#include "qmlviewer.h"

QmlViewer *QmlViewer::m_instance;

/*!
  \class QmlViewer
  \brief A wrapper for QmlApplicationViewer to get access to touch events.
         The signal touchEventReceived is grabbed by an instance of TouchEvents class,
         which is created from QML. For this to work, it needs an access to
         QmlViewer instance, therefore the static instance member.
*/
QmlViewer::QmlViewer()
{
    // We'd like to have touch events.
    setAttribute(Qt::WA_AcceptTouchEvents);
    m_instance = this;
}

QmlViewer *QmlViewer::instance() {
    return m_instance;
}

bool QmlViewer::event(QEvent *event) {

    // Grab touch events and signal appropriately.

    if (event->type() == QEvent::TouchBegin || event->type() == QEvent::TouchUpdate) {
        QTouchEvent *te = static_cast<QTouchEvent*>(event);
        foreach (QTouchEvent::TouchPoint tp, te->touchPoints()) {
            if (tp.state() == Qt::TouchPointPressed) {
                emit touchEventReceived(tp.screenPos().x(), tp.screenPos().y());
            }
        }
        return true;
    }
    return QmlApplicationViewer::event(event);
}

