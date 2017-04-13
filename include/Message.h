/*
 * Message.h
 * Created on 10 apr. 2017
 * Author: group 1
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <vector>
#include <string>
#include "Security.h"
#include "Message.pb.h"
#include "Packet.pb.h"

class Message {
public:
    Message();

    Message(std::string name, std::string receiver, std::string *data, bool is_file);

    virtual ~Message();

    // Loads the data for the Message
    void createMessage(std::string name, std::string receiver, std::string *data, bool is_file);

    void loadFromProto(pb::Message* proto); // Load Message from Protobuf
    void getMessage(pb::Message* proto);    // Get the Protobuf representation of the Message

    // Split the message into messages of max_msg_length payloads
    void splitForRaft(std::vector<pb::Message> *ret_obj, int max_msg_length);

    // Assemble the received messages
    bool assembleMessage(std::vector<pb::Message> *msgs);

    bool isFile();   // If the message includes text, or byte stream
private:
    std::string name;
    std::string *data;
    std::string receiver;
    bool is_file;
};

#endif /* MESSAGE_H_ */
