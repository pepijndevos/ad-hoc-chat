/*
 * Packet.h
 *
 *  Created on: 9 apr. 2017
 *      Author: Antonis Katzourakis & Eva Knol
 group: 3
 */

#ifndef PACKET_H_
#define PACKET_H_

#include <vector>
#include <iostream>

class Packet {
public:
	Packet();
	virtual ~Packet();
	void createPacket();
private:
	int seq;
	int msg_id;
	int ack;
	std::vector<int> checksum;
	std::vector<int> payload;
};

#endif /* PACKET_H_ */
