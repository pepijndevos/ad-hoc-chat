/*
 * RaftNode.cpp
 *
 *  Created on: 9 apr. 2017
 *      Author: Antonis Katzourakis & Eva Knol
 group: 3
 */

#include "RaftNode.h"

RaftNode::RaftNode() :
term_counter(0),
send_q(0),
received_q(0),
timer(0),
is_leader(false),
is_connected(false),
is_candidate(false),
prev_term(0),
prev_index(0){
	// TODO Auto-generated constructor stub

}

RaftNode::~RaftNode() {
	// TODO Auto-generated destructor stub
}

// checks the value of the timer by time now - timer
time_t RaftNode::checkTimer(){
	time_t time_now(0);
	return time_now-timer;
}

// update the time if a new leader is chosen or add the heartbeat to timer
void RaftNode::updateTimer(){
	if(/*connected to new leader*/){
		timer(0);
	}
	if(/*received_q is changed*/){
		timer=timer+10;
	}
}
void RaftNode::sendMessage(){

}
void RaftNode::messageReceived(){

}
void RaftNode::electLeader(){

}
