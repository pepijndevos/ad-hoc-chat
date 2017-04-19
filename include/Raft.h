/*
 * Raft.h
 *
 *  Created on: 11 apr. 2017
 *  group: 1
 */

#ifndef RAFT_H_
#define RAFT_H_

#define HANDLE_STATE_TIMER  300         // in ms
#define TIMER_EXPIRE        10          // in sec
#define HEART_BEAT_INCR     6           // in sec
#define NODES               4
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

    std::vector<pb::RaftMessage> queue_update;

    void receivedMessage(pb::RaftMessage *msg);
    void sendMessage(pb::Message *data, std::string receiver_ip);

    void setMyIp(uint32_t ip);
    void setMyIp(std::string ip);
    void resetFlags(pb::RaftMessage *msg);
    void setRouter(Router *router);

public slots:
    void handleState();
    void packetReceived(pb::Packet *pkt);

signals:
    void messageReceived(pb::Message *msg);

private:
    std::vector<pb::RaftMessage> log_local;
    std::vector<QUEUESEND> queue_send_stuf;
    std::vector<QUEUELEADER> queue_leader;

    STATES state;
    time_t timer;
    time_t special_timer;			// timer for leader and candidate
    time_t time_now;

    Router *router;
    pb::Message data;
    pb::RaftMessage send;

    std::string my_ip;
    uint32_t my_ip_int;

    int prev_log_size;
    int vote;
    int current_term;
    int index;
    int not_vote;
    int msg_id;
    int good_ack_back;

    bool first_time_candidate;
    bool first_time;
    bool leader_can_send;
    bool is_updated;

    void checkTimer();
    void sendRaftMessage(pb::RaftMessage *send);
    void follower();
    void candidate();
    void leader();
};

#endif /* RAFT_H_ */
