/*
 * Routing.cpp
 *
 *  Created on: 9 apr. 2017
 *      Author: Antonis Katzourakis & Eva Knol
 group: 1
 */

#include "Routing.h"
#include <vector>
#include "Packet.h"

Routing::Routing() {
	// TODO Auto-generated constructor stub

}

Routing::~Routing() {
	// TODO Auto-generated destructor stub
}

int Routing::incrementSeq(int seq){
	return seq+1;

}

bool Routing::isNew(){

	int pktcnt = 0; 	//set a counter to know how many packets are at the node.

	//if the packet is new it should be stored in the received packets vector string.
	//Here the whole packet with its contents is stored.

	//for every node check if there is already a packet.

	if(pktcnt == 1){
		//if there is a packet, check for the sequence number.

		if(){
			//if the sequence number is higher, drop the packet.

			//else add the packet to the received_data
			std::string<char>received_data = Packet();
		}
	}
	std::string<char>received_data = Packet();
	pktcnt = 1;		//set pktcnt to 1. Now we know there is a packet at the node.
	return true;
}

void Routing::forward(){
	//will determine which nodes should get the packet that is received from the sender. This means
	//that this function should flood the packets to everyone except to the one that is was sended.
	//Beware that the sequence number should also be increased.


}
