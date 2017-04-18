#include "router.h"
#include <QTimer>

Router::Router(Transceiver *t, QObject *parent) : QObject(parent), transceiver(t) {
    pending = new QHash<unsigned int, pb::Packet>();
    seen = new QSet<QPair<quint32, quint32>>();
    connect(t, &Transceiver::messageReceived,
            this, &Router::routeMessage);

    QSettings settings;
    QHostAddress ip(settings.value("ip").toString());
    my_ip = ip.toIPv4Address();
}

void Router::sendMessage(pb::Packet p) {
    unsigned int sn = rand();
    p.set_sequence_number(sn);
    p.set_ttl(1); // only forward once

    pending->insert(sn, p);
    QTimer::singleShot(200, this, [this, sn] () {retransmit(sn); });

    transceiver->sendMessage(p);
}

void Router::routeMessage(pb::Packet p) {
    if (p.sender_ip() == my_ip) return;

    // no destination == for everyone
    bool to_me = p.receiver_ip_size() == 0;
    for(auto ip : p.receiver_ip()) {
        if(ip == my_ip) to_me = true;
    }

    if (to_me) {
        if (p.message_type() == pb::Packet::ACK) {
            handleAck(p);
        } else {
            pb::Packet ack;
            ack.set_message_type(pb::Packet::ACK);
            ack.set_acknowledgment_number(p.sequence_number());
            ack.set_ttl(1); // only forward once
            ack.set_sender_ip(my_ip);
            ack.add_receiver_ip(p.sender_ip());

            transceiver->sendMessage(ack);

            QPair<quint32, quint32> msgid(p.sender_ip(), p.sequence_number());
            if (!seen->contains(msgid)) {
                seen->insert(msgid);
                emit messageReceived(p);
            }
        }
    }

    if (p.ttl() > 0) {
        flood(p);
    }
}

void Router::retransmit(unsigned int sn) {
    if(pending->contains(sn)) {
        QTimer::singleShot(200, this, [this, sn] () {retransmit(sn); });
        pb::Packet p = pending->value(sn);
        transceiver->sendMessage(p);
    }
}

void Router::handleAck(pb::Packet p) {
    // Possibly we need to handle ACk
    // from multiple people before 
    // we consider it delivered
    pending->remove(p.acknowledgment_number());
}

void Router::flood(pb::Packet p) {
    p.set_ttl(p.ttl()-1);
    transceiver->sendMessage(p);
}
