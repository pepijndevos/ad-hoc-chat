#pragma once

#include <QObject>
#include <QHash>
#include <QSet>
#include <QPair>
#include <QHostAddress>
#include "transceiver.h"

class Router : public QObject {
    Q_OBJECT

public:
    explicit Router(Transceiver *t, QObject *parent = 0);

public slots:
    void sendMessage(pb::Packet);
    void sendQueuedMessage(pb::Packet);
    void routeMessage(pb::Packet);

    void retransmit(unsigned int sn, unsigned int count);

signals:
    void messageReceived(pb::Packet);

private:
    void handleAck(pb::Packet);
    void flood(pb::Packet);
    int sendWindow;
    quint32 my_ip;
    Transceiver *transceiver;
    QHash<unsigned int, pb::Packet> *pending;
    QQueue<pb::Packet> *sendQueue;
    QSet<QPair<quint32, quint32>> *seen;
};
