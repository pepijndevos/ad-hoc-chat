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
    void sendMessage(pb::Packet *pkt);
    void routeMessage(pb::Packet *pkt);

    void retransmit(unsigned int sn, unsigned int count);

signals:
    void messageReceived(pb::Packet *pkt);
    void presenceUpdated(qint32 ip);

private:
    void handleAck(pb::Packet *pkt);
    void flood(pb::Packet *pkt);
    quint32 my_ip;
    Transceiver *transceiver;
    QHash<unsigned int, pb::Packet> *pending;
    QSet<QPair<quint32, quint32>> *seen;
};
