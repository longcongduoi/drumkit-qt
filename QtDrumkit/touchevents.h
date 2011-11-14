/**
 * Copyright (c) 2011 Nokia Corporation.
 * All rights reserved.
 *
 * Part of the QtDrumkit
 *
 * For the applicable distribution terms see the license text file included in
 * the distribution.
 */

#ifndef TOUCHEVENTS_H
#define TOUCHEVENTS_H

#include <QObject>

// Touch events object to be used from QML. Contains only one signal.
class TouchEvents : public QObject
{
    Q_OBJECT
public:
    TouchEvents(QObject *parent = 0);
signals:
    void touchEventReceived(int x, int y);
};

#endif // TOUCHEVENTS_H
