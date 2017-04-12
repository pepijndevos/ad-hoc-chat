/*
 * Message.cpp
 * Created on 10 apr. 2017
 * Author: group 1
 */

#include "Message.h"

Message::Message():
    msg_id(0),
    sender(""),
    payload(""),
    checksum(""){
    /* Default constructor */
    flags = createFlags(false, false, false, false);
}

Message::Message(std::string payload, int msg_id, std::string sender, std::string receiver,
               bool connected, bool leader, bool vote, bool candidate){
    /* Constructor with initialisation */
    createMessage(payload, msg_id, sender, receiver, connected, leader, vote, candidate);
}

Message::~Message() {
}

void Message::createMessage(std::string payload, int msg_id, std::string sender, std::string receiver,
                          bool connected, bool leader, bool vote, bool candidate){
    /* Load the Message Data */
    this->payload = payload;
    this->msg_id = msg_id;
    this->sender = sender;
    this->receiver = receiver;
    this->flags = createFlags(connected, leader, vote, candidate);
    this->checksum = getChecksum();
}

void Message::getMessage(MessageProto::Message* proto){
    /* Get the MessageProto representation of the Message */
    proto->set_msg_id(msg_id);
    proto->set_sender(sender);
    proto->set_checksum(checksum);
    proto->set_payload(payload);

    // Flags order: connected->leader->vote->candidate
    if(flags.connected)
        proto->add_flags(MessageProto::Message::CONNECTED);

    if(flags.leader)
        proto->add_flags(MessageProto::Message::LEADER);

    if(flags.vote)
        proto->add_flags(MessageProto::Message::VOTE);

    if(flags.candidate)
        proto->add_flags(MessageProto::Message::CANDIDATE);
}

void Message::loadFromProto(MessageProto::Message* proto){
    /* Load Message from Protobuf */
    msg_id = proto->msg_id();
    sender = proto->sender();
    checksum = proto->checksum();
    payload = proto->payload();

    // Load flags
    flags = createFlags(false, false, false, false);
    for(int f=0; f < proto->flags_size(); f++){
        switch (proto->flags(f)){
            case MessageProto::Message::CONNECTED:
                flags.connected = true;
                break;
            case MessageProto::Message::LEADER:
                flags.leader = true;
                break;
            case MessageProto::Message::VOTE:
                flags.vote = true;
                break;
            case MessageProto::Message::CANDIDATE:
                flags.candidate = true;
                break;
            default:
                break;
        }
    }
}

Flags Message::createFlags(bool connected, bool leader, bool vote, bool candidate){
    /* Create a flags struct */
    Flags rt_obj;
    rt_obj.connected = connected;
    rt_obj.leader = leader;
    rt_obj.vote = vote;
    rt_obj.candidate = candidate;
    return rt_obj;
}

std::string Message::getChecksum(){
    /* Calculate the checksum of the Message */
    std::string ck = std::to_string(msg_id) + payload + sender + receiver;
    ck += flags.connected ? "1" : "0";
    ck += flags.leader ? "1" : "0";
    ck += flags.vote ? "1" : "0";
    ck += flags.candidate ? "1" : "0";

    return Security::getMD5sum(ck);
}
