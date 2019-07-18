#ifndef QUDPSERVER_H
#define QUDPSERVER_H

#include <QException>
#include <QObject>
#include <QUdpSocket>

#define PACKET_MAX_DATA_LEN 128
#define PACKET_START_TOKEN '#'
#define PACKET_END_TOKEN '$'

typedef struct
{
    struct Header {
        quint8 StartToken;
        quint8 DataLen;
        qint16 CRC;
    } Header;
    QVector<quint8> Data;

} Packet;

class QUdpServer : public QObject {
    Q_OBJECT
public:
    enum class ServerStatus {
        STARTED,
        STOPPED
    };

    QUdpServer(quint16 port, QObject* parent = nullptr);
    ~QUdpServer();
    void Start(quint16 port = 0);
    void Stop();

signals:
    void OnPacketReceived(Packet* Packet);

public slots:
    void readyRead();

private:
    enum class PacketState {
        WAIT_START_TOKEN,
        WAIT_DATA_LENGTH,
        WAIT_DATA,
        WAIT_PACKET_END_TOKEN,
    };

    quint16 Port;
    QUdpSocket* socket = nullptr;
    ServerStatus CurrentStatus = ServerStatus::STOPPED;
    PacketState CurrentPacketState = PacketState::WAIT_START_TOKEN;
    Packet CurrentPacket;

    void ProcessByte(quint8 byte);
    void ClearPacket();
};

struct Exception : public std::exception {
    std::string s;
    explicit Exception(std::string ss)
        : s(ss)
    {
    }
    Exception(std::string function, std::string ss)
        : s(function + "(): " + ss)
    {
    }
    ~Exception() throw() override {} // Updated
    const char* what() const throw() override { return s.c_str(); }
};

#endif // QUDPSERVER_H
