/*
 * RaftNode.h
 *
 */

#ifndef RAFTNODE_H_
#define RAFTNODE_H_

#include <time.h>
#include <vector>
#include "Packet.h"

#define TIMER_EXPIRE 2
#define HEART_BEAT_INCR 5
#define WAIT_EXPIRE 6
#define MAX_NODES 4

class RaftNode {
public:
	RaftNode();
	virtual ~RaftNode();
	int term_counter;
	int send_q;
	std::vector<std::string> received_q;
	void sendMessage();
	void checkTimer();

private:
	time_t timer;
	bool is_leader;			// true when i am leader
	bool is_connected;		// am I connected to the leader, yes=true
	bool is_candidate;
	int prev_term;			// previous term
	int prev_index;			// node where you got the last message from
	int size_received_q;
    int vote;			// how many votes you got
	bool voting;			// I am voting
	bool is_waiting;
	time_t wait_time;

    void updateTimer();
    void messageReceived(Packet new_packet);
    void electLeader();		// chose how is the leader
};

#endif /* RAFTNODE_H_ */
