/*
 * Packet.h
 * Created on 10 apr. 2017
 * Author: group 1
 */

#ifndef PACKET_H_
#define PACKET_H_

#include <vector>
#include <string>
#include "Security.h"

struct packet_repr{
    int seq;
    int msg_id;
    int ack;
    std::string sender_id;
    std::string flags;
    std::string payload;
    std::string checksum;
};            // struct representation of the Packet

class Packet {
public:
    Packet();
	virtual ~Packet();

    void createPacket(std::string payload, int seq, int msg_id, int ack, std::string sender_id,
                        bool connected, bool leader, bool vote, bool candidate);          // Return the packet
    void loadFromStruct(packet_repr payload);  // Load a packet

    packet_repr getPacket();        // Get the string representation of the packet
    std::string createFlags(        // Create a flags string for the payload
            bool connected, // Is the node connected
            bool leader,    // Is the node the leader
            bool vote,      // Is the node voting for this leader
            bool candidate  // Is the node a leader candidate
        );
    std::string getChecksum();      // Calculate the checksum of the Packet
private:
	int seq;
	int msg_id;
	int ack;
    std::string sender_id;
    std::string flags;
    std::string payload;
    std::string checksum;
    struct repr;            // struct representation of the Packet
};

#endif /* PACKET_H_ */
