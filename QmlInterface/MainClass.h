#ifndef MAINCLASS_H
#define MAINCLASS_H

#include <QThread>
#include <QtDebug>

class MainClass : public QThread
{
    Q_OBJECT
public:
    MainClass();
    virtual ~MainClass() {}

public slots:
    void on_ButtonClicked();

private:
    void run();
};

#endif // MAINCLASS_H
