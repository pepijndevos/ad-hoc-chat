/*
 * Routing.cpp
 *
 *  Created on: 9 apr. 2017
 *  group: 1
 */

#include "Routing.h"
#include <vector>
#include "Packet.h"

Routing::Routing() {
}

Routing::~Routing() {
}

void Routing::incrementSeq(Packet *pkt){
    /* Increment sequence number of packet */
    packet_repr pkt_struct = pkt->getPacket();
    pkt_struct.seq = pkt_struct.seq+1;
    pkt->loadFromStruct(pkt_struct);
}

bool Routing::isNew(Packet *pkt){
    /* Check if a packet is new */
    packet_repr pkt_struct = pkt->getPacket();

    for(auto p: received_data){
        packet_repr temp_pkt_struct = p->getPacket();
        if(pkt_struct.msg_id == temp_pkt_struct.msg_id
                &&
           pkt_struct.seq > temp_pkt_struct.seq
        ){
            // it is an old packet
            return false;
        }
    }

    received_data.push_back(pkt);
    return true;
}

void Routing::forward(Packet *pkt){
    //will determine which nodes should get the packet that is received from the sender. This means
    //that this function should flood the packets to everyone except to the one that is was sent.
    //Beware that the sequence number should also be increased.
    incrementSeq(pkt);

    if(isNew(pkt) == false)
        return;

    // TODO flood the packet to everyone that is needed

}
