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

struct Flags{
    bool connected;
    bool leader;
    bool vote;
    bool candidate;
};

class Message {
public:
    Message();
    Message(std::string payload, int msg_id, std::string sender, std::string receiver,
                   bool connected, bool leader, bool vote, bool candidate);

    virtual ~Message();

    void createMessage(std::string payload, int msg_id, std::string sender, std::string receiver,
                      bool connected, bool leader, bool vote, bool candidate); // Loads the data for the Message

    void loadFromProto(MessageProto::Message* proto); // Load Message from Protobuf
    void getMessage(MessageProto::Message* proto);     // Get the Protobuf representation of the Message

    Flags createFlags(        // Create the flags struct
            bool connected, // Is the node connected
            bool leader,    // Is the node the leader
            bool vote,      // Is the node voting for this leader
            bool candidate  // Is the node a leader candidate
        );

    std::string getChecksum();      // Calculate the checksum of the Message

private:
    int msg_id;
    std::string sender;
    std::string receiver;
    Flags flags;
    std::string payload;
    std::string checksum;
};

#endif /* MESSAGE_H_ */
