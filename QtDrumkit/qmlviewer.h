/**
 * Copyright (c) 2011 Nokia Corporation.
 * All rights reserved.
 *
 * Part of the QtDrumkit
 *
 * For the applicable distribution terms see the license text file included in
 * the distribution.
 */

#ifndef QMLVIEWER_H
#define QMLVIEWER_H

#include "qmlapplicationviewer.h"

/*!
  \class QmlViewer
  \brief A wrapper for QmlApplicationViewer to get access to touch events.
         The signal touchEventReceived is grabbed by an instance of TouchEvents class,
         which is created from QML. For this to work, it needs an access to
         QmlViewer instance, therefore the static instance member.
*/
class QmlViewer : public QmlApplicationViewer
{
    Q_OBJECT
public:
    QmlViewer();
    bool event(QEvent *event);
    static QmlViewer *instance();
signals:
    void touchEventReceived(int x, int y);
private:
    static QmlViewer *m_instance;
};

#endif // QMLVIEWER_H
