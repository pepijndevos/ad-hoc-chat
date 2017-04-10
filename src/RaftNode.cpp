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
    voting(false){
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
        }else if(size_received_q != received_q.size()){   // I received a new packet/heartbeat
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
    if(is_leader){                      // I am the leader so I can send my data
            // message with data
    }else if(is_candidate){             // I am candidate so I send vote on me packet
            // message with I am candidate
    }else if(is_connected){             // I am connected so send packet to leader or the possible candidate
        if(voting){
                // message with I vote for you
        }else if(!voting){
                // message to leader
        }
    }
}

// put new packet in the received queue
void RaftNode::messageReceived(Packet rcv_packet){
    // TODO term_counter is the received one

    packet_repr new_packet = rcv_packet.getPacket();

    if(new_packet.flags[3]=='1' && !voting){	// I am going to vote on you and I didn't vote on someone else
        voting=true;
        is_connected=true;
        is_leader=false;
    } else if(is_connected){
        if(new_packet.flags[2]=='1'){		// increase how many votes I have
            vote+=1;
        }else if(new_packet.flags[1]=='1'){		// you are connected to a leader and received a new packet
            received_q.push_back(new_packet.payload);
        }else if(new_packet.flags[0]=='1'){         // got response from nodes
             // do stuff
        }
    }
    sendMessage();
}

// chose how is the leader
void RaftNode::electLeader(){
    if (voting == false){
        return;
    }

    if(is_candidate){
        if(vote >= MAX_NODES/2){		// I got the most votes, I am now the leader
            is_leader=true;
            term_counter+=1;
        }
        is_candidate=false;
    }

    vote=0;
    voting=false;
}
