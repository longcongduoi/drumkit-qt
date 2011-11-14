#ifndef TOUCHEVENTS_H
#define TOUCHEVENTS_H

#include <QObject>

// Touch events object to be used from QML. Contains only one signal.
class TouchEvents : public QObject
{
    Q_OBJECT
public:
    TouchEvents(Qbject* parent);
signals:
    void touchEventReceived(int x, int y);
};

#endif // TOUCHEVENTS_H
