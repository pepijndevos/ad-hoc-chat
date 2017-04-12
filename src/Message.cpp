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
    text = "";
    *file_data = "";
}

Message::Message(std::string name, std::string receiver, std::string text, std::string *file_data){
    /* Constructor with initialisation */
    createMessage(name, receiver, text, file_data);
}

Message::~Message() {
}

void Message::createMessage(std::string name, std::string receiver, std::string text, std::string *file_data){
    /* Load the Message Data */
    this->text = text;
    this->name = name;
    this->receiver = receiver;
    this->file_data = file_data;
}

void Message::getMessage(pb::Message* proto){
    /* Get the MessageProto representation of the Message */
    proto->set_name(name);
    proto->set_receiver(receiver);
    proto->set_text(text);
    proto->set_file_data(*file_data);
}

void Message::loadFromProto(pb::Message* proto){
    /* Load Message from Protobuf */
    name = proto->name();
    receiver = proto->receiver();
    text = proto->text();
    *file_data = proto->file_data();
}

MessageType Message::getType(){
    /* Get the type of the message */
    MessageType rt_obj;
    if(text.length() > 0)
        rt_obj.has_text = true;

    if(file_data->size() > 0)
        rt_obj.has_raw = true;

    return rt_obj;
}
