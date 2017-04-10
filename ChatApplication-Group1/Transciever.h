/*
 * Transciever.h
 *
 *  Created on: 9 apr. 2017
 *      Author: Antonis Katzourakis & Eva Knol
 group: 3
 */

#ifndef TRANSCIEVER_H_
#define TRANSCIEVER_H_

#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string>
#include <cstring>
#include <stdio.h>
#include <stdexcept>
#include <iostream>
#include "BlockingQueue.h"
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <cstring>

class Transciever {
public:
	Transciever();
	virtual ~Transciever();
	int sendPacket(std::string ip, unsigned int port, std::string group);
	int getReceiveSocket( std::string ip, uint16_t port, std::string group);
	int receivePacket(std::string ip, unsigned int port, std::string group, BlockingQueue<std::string> &q);

private:
	int q_send;
	int q_received;
	int max_payload_size;
	int q_ack;
	int last_ack;
	void checkPacket();
	void splitData();
	void assembleData();
	void checkRetransmit();
};

#endif /* TRANSCIEVER_H_ */
