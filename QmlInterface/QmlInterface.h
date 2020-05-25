#ifndef QMLINTERFACE_H
#define QMLINTERFACE_H

#include <QObject>
#include <QDebug>
#include <QQmlApplicationEngine>
#include <QQmlContext>

class QmlInterface : public QObject
{
    Q_OBJECT
public:
    explicit QmlInterface();
    virtual ~QmlInterface();
    void SetupUI();

public slots:
    Q_INVOKABLE void buttonClicked();
signals:
    void onButtonClicked();
private:
    QQmlApplicationEngine *engine;
};

#endif // QMLINTERFACE_H
