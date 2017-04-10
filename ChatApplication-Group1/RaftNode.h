/*
 * RaftNode.h
 *
 *  Created on: 9 apr. 2017
 *      Author: Antonis Katzourakis & Eva Knol
 group: 3
 */

#ifndef RAFTNODE_H_
#define RAFTNODE_H_

#include <time.h>

class RaftNode {
public:
	RaftNode();
	virtual ~RaftNode();
	int term_counter;
	int send_q;
	int received_q;
	void sendMessage();
	time_t checkTimer();

private:
	time_t timer;
	bool is_leader;
	bool is_connected;
	bool is_candidate;
	int prev_term;
	int prev_index;
	void updateTimer();
	void messageReceived();
	void electLeader();
};

#endif /* RAFTNODE_H_ */
