#include <QCoreApplication>
#include <QDebug>
#include <QThread>

#include "QUdpServer.h"

#define cout qDebug()

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);

    QUdpServer server(1337);

    return a.exec();
}
