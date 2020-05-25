#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "QmlInterface.h"
#include "MainClass.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    /* Ui Stuff */
    QmlInterface qml;
    qml.SetupUI();

    /* Main class */
    MainClass work;
    QObject::connect(&qml, SIGNAL(onButtonClicked()), &work, SLOT(on_ButtonClicked()) );

    return app.exec();
}
