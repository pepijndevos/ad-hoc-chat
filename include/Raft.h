/*
 * Raft.h
 *
 *  Created on: 11 apr. 2017
 *  group: 1
 */

#ifndef RAFT_H_
#define RAFT_H_

#define HANDLE_STATE_TIMER  100         // in ms
#define TIMER_EXPIRE        10          // in sec
#define NODES               4
#define HEART_BEAT_INCR     6           // in sec
#define MAX_SIZE            500

#include <QObject>

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <map>
#include <time.h>
#include <stdlib.h>

#include "utils.h"
#include "router.h"
#include "Message.h"

#include "Packet.pb.h"
#include "RaftMessage.pb.h"
#include "Message.pb.h"

struct QUEUESEND{
    pb::Message data;
    std::string sender_ip;
    std::string receiver_ip;
};

struct QUEUELEADER{
    QUEUESEND queue_send;
    int index;
};

enum STATES{
    FOLLOWER,
    CANDIDATE,
    LEADER
};

class Raft: public QObject {
    Q_OBJECT

public:
    Raft();
    virtual ~Raft() {};

    void receivedMessage(pb::RaftMessage new_message);
    void sendMessage(pb::Message *data, std::string receiver_ip);
    std::vector<pb::RaftMessage> queue_update;

    void setMyIp(int32_t ip);
    void setMyIp(std::string ip);
    void setRouter(Router *router);

public slots:
    void handleState();

signals:
    void messageReceived(pb::Message *msg);

private:
    STATES state;
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
    int32_t my_ip_int;
    bool is_updated;
    Router *router;

    void checkTimer();
    void sendRaftMessage(pb::RaftMessage *send);
    void follower();
    void candidate();
    void leader();
};

#endif /* RAFT_H_ */
