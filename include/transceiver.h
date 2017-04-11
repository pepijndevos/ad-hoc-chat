#ifndef TRANSCEIVER_H_
#define TRANSCEIVER_H_

#include <QtWidgets>
#include <QtNetwork>
#include "Routing.h"
#include "Packet.h"
#include "Message.pb.h"

class Transceiver : public QObject {
    Q_OBJECT

public:
    explicit Transceiver(QObject *parent = 0);

public slots:
    void sendMessage(QByteArray data);
    void sendString(std::string data);
    void processPendingDatagrams();
signals:
    void messageReceived(quint8 source, QByteArray data);

private:
    QHostAddress groupAddress;
    QUdpSocket *udpSocket;
    Routing router;

    MessageProto::Message parseRecvd(QByteArray datagram);
};

#endif // TRANSCEIVER_H_
