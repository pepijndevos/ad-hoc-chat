#ifndef TRANSCEIVER_H_
#define TRANSCEIVER_H_

#include <QtWidgets>
#include <QtNetwork>
#include "Packet.pb.h"

class Transceiver : public QObject {
    Q_OBJECT

public:
    explicit Transceiver(QObject *parent = 0);

public slots:
    void sendMessage(pb::Packet *pkt);
    void processPendingDatagrams();

signals:
    void messageReceived(pb::Packet *pkt);

private:
    QHostAddress groupAddress;
    QUdpSocket *udpSocket;
};

#endif // TRANSCEIVER_H_
