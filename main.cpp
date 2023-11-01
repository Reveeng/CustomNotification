#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "DeviceNotificationWindowController.h"
#include <QTimer>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);
    DeviceNotificationWindowController controller;
    QTimer timer;
    int counter = 0;
    QObject::connect(&timer, &QTimer::timeout, [&controller, &counter](){
        Test *t = new Test();
        t->connection = "AAAA" + QString::number(counter);
        t->name = "BBBBB";
        controller.newDeviceHandle(t);
        counter++;
    });
    timer.start(3000);
//    QQmlApplicationEngine engine;
//    const QUrl url(QStringLiteral("qrc:/main.qml"));
//    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
//        &app, [url](QObject *obj, const QUrl &objUrl) {
//            if (!obj && url == objUrl)
//                QCoreApplication::exit(-1);
//        }, Qt::QueuedConnection);
//    engine.load(url);

//    QObject *root = engine.rootObjects()[0];
//    root->setProperty("deviceName","AAAA");
//    root->setProperty("connectionType","BABABA");

    return app.exec();
}
