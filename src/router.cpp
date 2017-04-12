#include "router.h"

Router::Router(Transceiver *t, QObject *parent) : QObject(parent), transceiver(t) {
    sequence_number = 0;
    connect(t, &Transceiver::messageReceived,
            this, &Router::routeMessage);
}

void Router::sendMessage(pb::Packet p) {
    p.set_sequence_number(sequence_number++);
    p.set_ttl(1); // only forward once
    transceiver->sendMessage(p);
}

void Router::routeMessage(pb::Packet p) {
    if (p.ttl() > 0) {
        flood(p);
    }

    if (p.message_type() == pb::Packet::ACK) {
        handleAck(p);
    } else { // TODO check if we're in receiver_ip
        emit messageReceived(p);
    }
}

void Router::handleAck(pb::Packet p) {
    //TODO
}

void Router::flood(pb::Packet p) {
    //TODO
    // retransmit with ttl-1
}
