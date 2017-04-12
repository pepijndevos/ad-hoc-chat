/*
 * Message.h
 * Created on 10 apr. 2017
 * Author: group 1
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <vector>
#include <string>
#include <QWidget>
#include "Security.h"
#include "Message.pb.h"

struct MessageType {
    bool has_text;
    bool has_raw;
};

class Message {
public:
    Message();

    Message(std::string name, std::string receiver, std::string text, std::string *file_data);

    virtual ~Message();

    void createMessage(std::string name, std::string receiver, std::string text, std::string *file_data); // Loads the data for the Message

    void loadFromProto(pb::Message* proto); // Load Message from Protobuf
    void getMessage(pb::Message* proto);    // Get the Protobuf representation of the Message

    MessageType getType();
private:
    std::string name;
    std::string text;
    std::string receiver;
    std::string *file_data;
};

#endif /* MESSAGE_H_ */
