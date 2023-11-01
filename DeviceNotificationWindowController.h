#ifndef DEVICENOTIFICATIONWINDOWCONTROLLER_H
#define DEVICENOTIFICATIONWINDOWCONTROLLER_H

#include <QObject>
#include <QPoint>
#include <QQueue>
#include <QVector>
#include <QQmlApplicationEngine>

class Test{
public:
    QString name;
    QString connection;
};


class DeviceNotificationWindowController : public QObject
{
    Q_OBJECT
public:
    DeviceNotificationWindowController(QObject *parent = nullptr);
    ~DeviceNotificationWindowController();

public slots:
    void newDeviceHandle(Test * dev);

private slots:
    void notificationWindowClosedHanlde();

private:
    void createWindowsCircle();

    void moveUpOpenedWindows();
    void manageWindows();
    void createNewNotification(QQmlApplicationEngine* engine,Test *dev);


    QPoint m_bottomRightAnglePos;

    QQueue<Test*> m_deviceQueue;

    int m_maxNotificationCount;
    QQueue<QQmlApplicationEngine*> m_closedNotifications;
    QQueue<QQmlApplicationEngine*> m_openedNotifications;
};

#endif // DEVICENOTIFICATIONWINDOWCONTROLLER_H
