#include "QUdpServer.h"

QUdpServer::QUdpServer(quint16 port, QObject* parent)
    : QObject(parent)
{
    this->Start(port);
}

QUdpServer::~QUdpServer()
{
    this->Stop();
}

void QUdpServer::Start(quint16 port)
{
    if (this->CurrentStatus == ServerStatus::STARTED) {
        throw Exception("Start()", "Already started!");
    }

    this->Port = port;

    // create a QUDP socket
    this->socket = new QUdpSocket(this);

    // The most common way to use QUdpSocket class is
    // to bind to an address and port using bind()
    // bool QAbstractSocket::bind(const QHostAddress & address,
    //     quint16 port = 0, BindMode mode = DefaultForPlatform)

    if (this->socket->bind(QHostAddress::Any, this->Port)) {

        connect(this->socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
        this->CurrentStatus = ServerStatus::STARTED;
        qDebug() << "Server started!";

    } else {
        //        socket = nullptr;
        throw Exception("Start", this->socket->errorString().toLocal8Bit().constData());
    }
}

void QUdpServer::Stop()
{
    if (this->socket != nullptr) {
        this->CurrentStatus = ServerStatus::STOPPED;

        try {
            socket->disconnectFromHost();
            socket->close();
            delete this->socket;
            socket = nullptr;
            qDebug() << "Server stopped!";

        } catch (...) {
        }
    }
}

void QUdpServer::readyRead()
{
    char CurrByte;
    while (this->socket->hasPendingDatagrams() && this->socket->getChar(&CurrByte)) {
        ProcessByte(static_cast<quint8>(CurrByte));
    }
}

void QUdpServer::ProcessByte(quint8 byte)
{
    if (this->CurrentPacketState == PacketState::WAIT_START_TOKEN) {
        if (byte == PACKET_START_TOKEN) {
            this->CurrentPacket.Header.StartToken = byte;
            this->CurrentPacketState = PacketState::WAIT_DATA_LENGTH;
        }
    }

    else if (this->CurrentPacketState == PacketState::WAIT_DATA_LENGTH) {
        if (byte <= PACKET_MAX_DATA_LEN) {
            this->CurrentPacket.Header.DataLen = byte;
            this->CurrentPacketState = PacketState::WAIT_DATA;
        } else {
            this->CurrentPacketState = PacketState::WAIT_START_TOKEN;
            this->ClearPacket();
        }
    }

    else if (this->CurrentPacketState == PacketState::WAIT_DATA) {

    }

    else if (this->CurrentPacketState == PacketState::WAIT_PACKET_END_TOKEN) {
    }
}

void QUdpServer::ClearPacket()
{
}
