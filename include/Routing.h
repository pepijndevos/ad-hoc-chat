/*
 * Routing.h
 *  group: 3
 */

#ifndef ROUTING_H_
#define ROUTING_H_

#include<vector>
#include<iostream>
#include "Packet.h"

class Routing {
public:
	Routing();
	virtual ~Routing();
    std::vector<Packet*> received_data;

private:
        void incrementSeq(Packet *pkt);
        bool isNew(Packet *pkt);
        void forward(Packet *pkt);
};

#endif /* ROUTING_H_ */
