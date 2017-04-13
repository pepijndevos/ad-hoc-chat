/*
 * Message.cpp
 * Created on 10 apr. 2017
 * Author: group 1
 */

#include "Message.h"

Message::Message(){
    /* Default constructor */
    name = "";
    receiver = "";
    *data = "";
}

Message::Message(std::string name, std::string receiver, std::string *data, bool is_file){
    /* Constructor with initialisation */
    createMessage(name, receiver, data, is_file);
}

Message::~Message() {
}

void Message::createMessage(std::string name, std::string receiver, std::string *data, bool is_file){
    /* Load the Message Data */
    this->name = name;
    this->receiver = receiver;
    this->data = data;
    this->is_file = is_file;
}

void Message::getMessage(pb::Message* proto){
    /* Get the MessageProto representation of the Message */
    proto->set_name(name);
    proto->set_receiver(receiver);
    proto->set_data(*data);
    proto->set_is_file(is_file);
}

void Message::loadFromProto(pb::Message* proto){
    /* Load Message from Protobuf. Assumes a complete message (not fragmented) */
    name = proto->name();
    receiver = proto->receiver();
    *data = proto->data();
    is_file = proto->is_file();
}

bool Message::isFile(){
    /* Is the message a file or text? */
    return is_file;
}

void Message::splitForRaft(std::vector<pb::Message> *ret_obj, int max_msg_length = 512){
    /* Encapsulate the message into RaftMessages protobufs. Stored in the given ret_obj vector */
    pb::Message t_proto;
    getMessage(&t_proto);

    t_proto.set_more(false);
    t_proto.set_msg_seq(0);

    ret_obj->push_back(t_proto);

    while(t_proto.data().length() > max_msg_length){
        // Split the data
        std::string prev_data = t_proto.data().substr(0, max_msg_length-1);
        std::string new_data =  t_proto.data().substr(max_msg_length-1, t_proto.data().length());

        // Pointer to the last pushed message
        pb::Message *last_msg = &(ret_obj->at(ret_obj->size()-1));

        // Update the data and update the more flag
        last_msg->set_data(prev_data);
        last_msg->set_more(true);

        // Create the next message with the new data and the new msg_seq
        pb::Message new_msg;
        getMessage(&t_proto);
        new_msg.set_data(new_data);
        new_msg.set_msg_seq(t_proto.msg_seq()+1);

        // Push it and update the t_proto
        ret_obj->push_back(new_msg);
        t_proto = new_msg;
    }
}

bool Message::assembleMessage(std::vector<pb::Message> *msgs){
    /* Assemble the message from a vector of messages.
     * Assumes the same msg_id, receiver and sender name.
     * It stores the result in this object.
     *
     * Returns true if successful. (complete message received)
     */
    std::vector<pb::Message> ordered_msgs;
    bool no_more = false;

    for(auto m: *msgs){
        if(ordered_msgs.size()-1 < m.msg_seq()){
            ordered_msgs.push_back(m);
        }else{
            ordered_msgs.insert(ordered_msgs.begin() + m.msg_seq(), m);
        }

        if(m.more() == false)
            no_more = true;
    }

    if (no_more == false)               // Didn't receive the whole message yet.
        return false;

    for(int i=0; i < ordered_msgs.size(); i++){
        pb::Message current_msg = ordered_msgs.at(i);
        if(current_msg.msg_seq() != i)   // No complete message yet (intermediate parts missing)
            return false;

        name = current_msg.name();
        receiver = current_msg.receiver();
        is_file = current_msg.is_file();

        *data += current_msg.data();
    }

    return true;
}
