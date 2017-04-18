/*
 * Message.h
 * Created on 10 apr. 2017
 * Author: group 1
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <vector>
#include <string>
#include <QString>

#include "utils.h"
#include "Message.pb.h"

class Message {
public:
    Message();
    Message(pb::Message *msg);
    virtual ~Message();

    pb::Message* getMessage();
    void setMessage(pb::Message *msg);

    // Split the message into messages of max_msg_length payloads
    void splitForRaft(std::vector<pb::Message> *ret_obj, int max_msg_length);

    // Assemble the received messages
    bool assembleMessage(std::vector<pb::Message> *msgs);

    // File messages
    Filetypes getFiletype();
    bool isFile();   // If the message includes text, or byte stream
private:
    pb::Message *msg;

};

#endif /* MESSAGE_H_ */
