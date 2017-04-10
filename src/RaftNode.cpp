/*
 * RaftNode.cpp
 *
 *  Created on: 9 apr. 2017
 *      Author: group 1
 */

#include "RaftNode.h"

RaftNode::RaftNode() :
term_counter(0),
send_q(0),
timer(0),
is_leader(false),
is_connected(false),
is_candidate(false),
prev_term(0),
prev_index(0),
size_received_q(0),
vote(0),
voting(false){
	// TODO Auto-generated constructor stub

}

RaftNode::~RaftNode() {
	// TODO Auto-generated destructor stub
}

// checks the value of the timer by time now - timer
void RaftNode::checkTimer(){
	time_t time_now(0);
	if(time_now-timer > 60){				// time out after 60 seconds, you are a candidate and got a updated/full timer
		is_candidate=true;
		is_connected=false;
	}
}

// update the time
void RaftNode::updateTimer(){
	if(is_leader){						// I am a leader so my timer is always updated/full
		timer=time(0);
	}else if (is_connected){			// I am connected to a leader
		if(prev_term!=term_counter){	// if my previous term and my term counter is different, it means that i am connected to a new leader, so full time
			timer=time(0);
			voting=false;
		}else if(size_received_q!=received_q.size()){			// I received a new packet/heartbeat
			timer=timer+10;
		}
	}
	prev_term=term_counter;
	size_received_q=received_q.size();
	checkTimer();
}

// send the right message
void RaftNode::sendMessage(){
	if(is_leader){						// I am the leader so I can send my data
		// message with data
	}else if(is_candidate){				// I am candidate so I send vote on me packet
		// message with I am candidate
	}else if(is_connected){				// I am connected so send packet to leader or the possible candidate
		if(voting){
			// message with I vote for you
		}else if(!voting){
			// message to leader
		}
	}
}

// put new packet in the received queue
void RaftNode::messageReceived(Packet rcv_packet){
	packet_repr new_packet = rcv_packet.getPacket();
	if(new_packet.flags[3]=="1" && !voting){	// I am going to vote on you and I didn't vote on someone else
		voting=true;
		is_connected=true;
	}
	else if(is_connected){
		if(new_packet.flags[2]=="1"){			// increase how many votes I have
			vote=+1;
		}else if(new_packet.flags[1]=="1"){		// you are connected to a leader and received a new packet
			received_q.push_back(new_packet.payload);
		}else if(new_packet.flags[0]=="1"){	// got response from nodes
			// do stuff
		}
		sendMessage();
		voting=false;
	}
}

// chose how is the leader
void RaftNode::electLeader(){
	if(is_candidate){
		if(vote>=2){					// I got the most votes, I am now the leader
			is_leader=true;
			is_candidate=false;
		}else{							// you have not the most votes
			is_leader=false;
			is_candidate=false;
		}
	}
	term_counter=+1;
	vote=0;
}
