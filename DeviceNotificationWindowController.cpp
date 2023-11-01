#include "DeviceNotificationWindowController.h"
#include <QGuiApplication>
#include <QScreen>
#include <QDebug>

DeviceNotificationWindowController::DeviceNotificationWindowController(QObject *parent):
    QObject(parent),
    m_maxNotificationCount(3)
{
    QScreen *mainScreen = QGuiApplication::screens()[0];
    m_bottomRightAnglePos.setX(mainScreen->availableGeometry().width());
    m_bottomRightAnglePos.setY(mainScreen->availableGeometry().height());
    createWindowsCircle();
}

DeviceNotificationWindowController::~DeviceNotificationWindowController(){
    for (auto engine : m_closedNotifications){
        engine->deleteLater();
    }
    for (auto engine : m_openedNotifications){
        engine->deleteLater();
    }
}

void DeviceNotificationWindowController::createWindowsCircle(){
    for (int i = 0; i < m_maxNotificationCount; ++i){
        QQmlApplicationEngine *engine =  new QQmlApplicationEngine();
        if (!engine){
            qDebug() << "Failed to create engine";
            return;
        }

        engine->load(QUrl("qrc:/main.qml"));
        QObject *rootObj = engine->rootObjects()[0];
        rootObj->setProperty("initialXPos",m_bottomRightAnglePos.x());
        rootObj->setProperty("initialYPos",m_bottomRightAnglePos.y());
        connect(rootObj, SIGNAL(closed()), this , SLOT(notificationWindowClosedHanlde()));
        m_closedNotifications.enqueue(engine);
    }
}

void DeviceNotificationWindowController::newDeviceHandle(Test *dev){
    m_deviceQueue.enqueue(dev);
    manageWindows();
}

void DeviceNotificationWindowController::notificationWindowClosedHanlde(){
    if (m_openedNotifications.size() == 0)
        return;
    m_closedNotifications.enqueue(m_openedNotifications.dequeue());
    manageWindows();
}

void DeviceNotificationWindowController::createNewNotification(QQmlApplicationEngine* engine,Test *dev){
    QObject *rootObj = engine->rootObjects()[0];
    rootObj->setProperty("deviceName", dev->name);
    rootObj->setProperty("connectionType", dev->connection);
    rootObj->setProperty("notificationNumber",1);
    rootObj->setProperty("visible", true);
    m_openedNotifications.enqueue(engine);
}

void DeviceNotificationWindowController::moveUpOpenedWindows(){
    for (auto engine : m_openedNotifications){
        QObject *root = engine->rootObjects()[0];
        int counter = root->property("notificationNumber").toInt();
        root->setProperty("notificationNumber", counter+1);
    }
}

void DeviceNotificationWindowController::manageWindows(){
    if (m_deviceQueue.empty())
        return;

    while (!m_deviceQueue.empty() && !m_closedNotifications.empty()){
        Test * dev = m_deviceQueue.dequeue();
        auto engine = m_closedNotifications.dequeue();
        moveUpOpenedWindows();
        createNewNotification(engine, dev);
    }
}
