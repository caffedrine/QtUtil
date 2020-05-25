#include "MainClass.h"

MainClass::MainClass()
{

}

void MainClass::on_ButtonClicked()
{
    qDebug() << "Button click received in main class!";

}

void MainClass::run()
{
    while(1)
    {
        QThread::sleep(1);
    }
}
