#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QObject>
#include<QQmlContext>
#include<QQuickStyle>
#include"VheicleDataSender/VheicleDataSender.h"
int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
QQuickStyle::setStyle("Imagine");
    QGuiApplication app(argc, argv);
VheicleDataSender Dsend;

    QQmlApplicationEngine engine;
//engine.rootContext()->setContextProperty("testing",&data);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);



   QQmlContext * rootContext=engine.rootContext();
   rootContext->setContextProperty("mainAccess",&Dsend);

    return app.exec();

}
