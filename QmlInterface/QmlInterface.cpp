#include "QmlInterface.h"

QmlInterface::QmlInterface()
{

}

QmlInterface::~QmlInterface()
{

}

void QmlInterface::SetupUI()
{
    engine = new QQmlApplicationEngine;
    engine->load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine->rootObjects().isEmpty())
    {
        qDebug() << "Failed to load UI";
    }
    else
    {
        engine->rootContext()->setContextProperty("cpp", this);
    }
}

void QmlInterface::buttonClicked()
{
    qDebug() << "Button clicked! Signal to be emited!";
    emit onButtonClicked();
}
