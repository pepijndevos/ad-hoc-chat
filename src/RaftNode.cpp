/*
 * RaftNode.cpp
 *
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
voting(false),
is_waiting(false),
wait_time(0){
}

RaftNode::~RaftNode() {
}

// checks the value of the timer by time now - timer
void RaftNode::checkTimer(){
	time_t time_now(0);
	if(time_now-timer > TIMER_EXPIRE){		// If the timer expires, you are a candidate and got a updated/full timer
		is_candidate=true;
		is_connected=false;
	}
}

// update the time
void RaftNode::updateTimer(){
	if(is_leader){                      // Leader's timer is not expiring
		timer=time(0);
	}else if (is_connected){            // If connected to the leader
		if(prev_term != term_counter){  // I am connected to a new leader, so update timer
			timer=time(0);
			voting=false;
		}else if(size_received_q != received_q.size()){   // I received a new message/heartbeat
			timer=timer + HEART_BEAT_INCR;
		}
	}
	prev_term=term_counter;
	size_received_q=received_q.size();
	checkTimer();
}

// send the right message
void RaftNode::sendMessage(){
	// TODO
	if(is_leader){                      // I can send my data
		// message with data
	}else if(is_candidate){             // I send vote on me message
		// message with I am candidate
	}else if(is_connected){             // send message to leader or the possible candidate
		if(voting){
			// message with I vote for you
		}else if(!voting){
			// message to leader
		}
	}
}

void RaftNode::messageReceived(Packet rcv_message){
	// TODO term_counter is the received one
	electLeader();
	packet_repr new_message = rcv_message.getPacket();

	if(new_message.flags[3]=='1' && !voting){	// I am going to vote on you and I didn't vote on someone else
		voting=true;
		is_connected=true;
		is_leader=false;
	} else if(is_connected){
		if(new_message.flags[2]=='1'){					// increase how many votes I have
			vote+=1;
		}else if(new_message.flags[1]=='1'){			// you are connected to a leader and received a new message
			received_q.push_back(new_message.payload);
		}else if(new_message.flags[0]=='1'){         	// got response from nodes
			// do stuff
		}
	}
	updateTimer();
	sendMessage();
}

// chose how is the leader
void RaftNode::electLeader(){
	if(is_candidate){
		time_t time_now=time(0);
		if((is_waiting && time_now-wait_time>WAIT_EXPIRE) || vote >= MAX_NODES/2){
			if(vote >= MAX_NODES/2){		// I got the most votes, I am now the leader
				is_leader=true;
				term_counter+=1;
			}
			is_candidate=false;
			vote=0;
			is_waiting=false;
		}else if(!is_waiting){
			is_waiting=true;
			wait_time=time(0);
		}
	}
	voting=false;
}
