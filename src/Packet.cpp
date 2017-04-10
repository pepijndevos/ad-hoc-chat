/*
 * Packet.cpp
 * Created on 10 apr. 2017
 * Author: group 1
 */

#include "Packet.h"

Packet::Packet():
	seq(0),
	msg_id(0),
    ack(0),
    sender_id("1"),
    payload(""),
    checksum(""){

}

Packet::~Packet() {
}

void Packet::createPacket(std::string payload, int seq, int msg_id, int ack, std::string sender_id,           // Data
                          bool connected, bool leader, bool vote, bool candidate){  // Flags
    /* Load the Packet Data */
    this->payload = payload;
    this->seq = seq;
    this->msg_id = msg_id;
    this->ack = ack;
    this->sender_id = sender_id;
    this->flags = createFlags(connected, leader, vote, candidate);
    this->checksum = getChecksum();
}

void Packet::loadFromStruct(packet_repr payload){
    /* Load Packet from received string */
    this->seq = payload.seq;
    this->ack = payload.ack;
    this->msg_id = payload.msg_id;
    this->flags = payload.flags;
    this->sender_id = payload.sender_id;
    this->payload = payload.payload;
    this->checksum = payload.checksum;
}

packet_repr Packet::getPacket(){
   /* Return the string representation of the packet
    * Format:
    * msg_id & seq & ack & flags & data
    */
    packet_repr p;
    p.seq = seq;
    p.ack = ack;
    p.msg_id = msg_id;
    p.flags = flags;
    p.payload = payload;
    p.checksum = checksum;
    return p;
}

std::string Packet::createFlags(bool connected, bool leader, bool vote, bool candidate){
    /* Create a flags string for the payload
     * Format:
     * connected leader vote candidate
     */
    std::string rt_string = "";
    rt_string += connected ? "1" : "0";
    rt_string += leader ? "1" : "0";
    rt_string += vote ? "1" : "0";
    rt_string += candidate ? "1" : "0";

    return rt_string;
}

std::string Packet::getChecksum(){
    /* Calculate the checksum of the Packet */
    std::string ck = std::to_string(seq) + std::to_string(ack) + std::to_string(msg_id);
    ck += flags + payload;
    return Security::getMD5sum(ck);
}
