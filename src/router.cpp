#include "router.h"
#include <QTimer>

Router::Router(Transceiver *t, QObject *parent) : QObject(parent), transceiver(t) {
    pending = new QHash<unsigned int, pb::Packet>();
    seen = new QSet<QPair<quint32, quint32>>();
    sendQueue = new QQueue<pb::Packet>();
    connect(t, &Transceiver::messageReceived,
            this, &Router::routeMessage);

    QSettings settings;
    QHostAddress ip(settings.value("ip").toString());
    my_ip = ip.toIPv4Address();
    sendWindow = 10;
}

void Router::sendQueuedMessage(pb::Packet p) {
    if(pending->size() < sendWindow) {
        sendMessage(p);
    } else {
        //qDebug("queued");
        sendQueue->enqueue(p);
    }
}

void Router::sendMessage(pb::Packet p) {
    unsigned int sn = rand();
    p.set_sequence_number(sn);
    p.set_ttl(1); // only forward once
    if(p.sender_ip() == 0) p.set_sender_ip(my_ip);

    if(p.message_type() != pb::Packet::VOIP) {
        pending->insert(sn, p);
        QTimer::singleShot(200, this, [this, sn] () {retransmit(sn, 5); });
    }

    if(!transceiver->sendMessage(p)) {
        sendWindow = (sendWindow >> 1) | 1;
        //qDebug() << sendWindow << "fail";
    }
}

void Router::routeMessage(pb::Packet p) {
    //if (p.sender_ip() == my_ip) return;

    // no destination == for everyone
    bool to_me = p.receiver_ip_size() == 0;
    for(auto ip : p.receiver_ip()) {
        if(ip == my_ip) to_me = true;
    }

    if (to_me) {
        if (p.message_type() == pb::Packet::ACK) {
            handleAck(p);
        } else {
            if(p.message_type() != pb::Packet::VOIP) {
                pb::Packet ack;
                ack.set_message_type(pb::Packet::ACK);
                ack.set_acknowledgment_number(p.sequence_number());
                ack.set_ttl(1); // only forward once
                ack.set_sender_ip(my_ip);
                ack.add_receiver_ip(p.sender_ip());

                transceiver->sendMessage(ack);
            }


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

void Router::retransmit(unsigned int sn, unsigned int count) {
    if(pending->contains(sn) && count > 0) {
        sendWindow = (sendWindow >> 1) | 1;
        count--;
        QTimer::singleShot(200, this, [this, sn, count] () {retransmit(sn, count); });
        pb::Packet p = pending->value(sn);
        transceiver->sendMessage(p);
        //qDebug() << sendWindow << "re";
    } else {
        // if it did not arrive after 5 tries, give up
        pending->remove(sn);
    }

    while(pending->size() < sendWindow && !sendQueue->isEmpty()) {
        //qDebug("dequeue");
        pb::Packet qp = sendQueue->dequeue();
        sendMessage(qp);
    }
}

void Router::handleAck(pb::Packet p) {
    int sn = p.acknowledgment_number();
    if(pending->contains(sn)) {
        //qDebug() << sn;
        pb::Packet pp = pending->value(sn);
        auto receivers = pp.mutable_receiver_ip();
        for (auto it = receivers->begin(); it != receivers->end(); it++) {
            //qDebug() << *it;
            if (p.sender_ip() == *it) {
                //qDebug() << p.sender_ip() << "erase";
                receivers->erase(it);
                break;
            }
        }
        if(pp.receiver_ip_size() > 0) {
            pending->insert(sn, pp);
        } else {
            pending->remove(sn);
        }
    }

    sendWindow++;
    //qDebug() << sendWindow << "ack";
    while(pending->size() < sendWindow && !sendQueue->isEmpty()) {
        //qDebug("dequeue");
        pb::Packet qp = sendQueue->dequeue();
        sendMessage(qp);
    }
}

void Router::flood(pb::Packet p) {
    p.set_ttl(p.ttl()-1);
    transceiver->sendMessage(p);
}
