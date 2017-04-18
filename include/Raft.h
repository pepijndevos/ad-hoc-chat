/*
 * Raft.h
 *
 *  Created on: 11 apr. 2017
 *      Author: Antonis Katzourakis & Eva Knol
 group: 3
 */

#ifndef RAFT_H_
#define RAFT_H_

#define TIMER_EXPIRE			60
#define NODES					4
#define HEART_BEAT_INCR			10
#define MAX_SIZE				500


#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <map>
#include <time.h>
#include "RaftMessage.pb.h"
#include "Message.pb.h"

//struct Message{
//	int msg_id;
//	std::string data;
//	int term_message;
//	std::string flags;
//	std::string ip_sender;
//	std::string ip_me_or_ip_data;	// the leader now to with which ip he deals and the follower knows to hows data is sended further
//	int index;						// how full is the queue?
//};

struct QUEUESEND{
    pb::Message data;
    std::string sender_ip;
    std::string receiver_ip;
};

struct QUEUELEADER{
    QUEUESEND queue_send;
    int index;
};

class Raft {
public:
    Raft();
    virtual ~Raft();
    void receivedMessage(pb::RaftMessage new_message);
    void iWantToSendStuff(pb::Message data, std::string receiver_ip);
    void handleState(std::string this_ip);
    std::vector<pb::RaftMessage> queue_update;

private:
    std::string state;
    time_t timer;
    time_t time_now;
    bool first_time_candidate;
    time_t special_timer;			// timer for leader and candidate
    std::vector<pb::RaftMessage> log_local;
    int prev_log_size;
    int vote;
    int current_term;
    bool first_time;
    std::vector<QUEUESEND> queue_send_stuf;
    int index;
    std::vector<QUEUELEADER> queue_leader;
    int not_vote;
    int msg_id;
    int good_ack_back;
    bool leader_can_send;
    pb::Message data;
    pb::RaftMessage send;
    std::string my_ip;
    bool is_updated;

    void checkTimer();
    void sendMessage(pb::RaftMessage send);
    void follower();
    void candidate();
    void leader();
};

#endif /* RAFT_H_ */
