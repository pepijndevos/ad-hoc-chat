/*
 * Raft.cpp
 *
 *  Created on: 11 apr. 2017
 *  group: 1
 */

#include "Raft.h"

Raft::Raft() :
    state(STATES::FOLLOWER),
    timer(0),
    time_now(0),
    first_time_candidate(true),
    special_timer(0),
    prev_log_size(0),
    vote(0),
    current_term(0),
    index(0),
    not_vote(0),
    msg_id(0),
    good_ack_back(0),
    is_updated(false){

//    log_local = std::vector<pb::RaftMessage>{};
//    queue_send_stuf = std::vector<QUEUESEND>{};
//    queue_leader = std::vector<QUEUELEADER>{};

    // Timer for handle state
    QTimer *handle_state_timer = new QTimer(this);
    connect(handle_state_timer, SIGNAL(timeout()), this, SLOT(handleState()));
    handle_state_timer->start(HANDLE_STATE_TIMER);
}

void Raft::packetReceived(pb::Packet *pkt){
    /* Received a new packet */
    pb::RaftMessage msg = pkt->raft_msg();
    receivedMessage(&msg);
}

void Raft::setMyIp(uint32_t ip){
    this->my_ip_int = ip;
    this->my_ip = utils::getIp(ip);
}

void Raft::setMyIp(std::string ip){
    this->my_ip = ip;
    this->my_ip_int = utils::getIp(ip);
}

/* Increment time if you got a message
 * Check what to send back
 * Send current term, a flag, my ip, data (first one that is in my queue or zero), my index value (how big my queue send stuff is), send message id from previous one
 *  */
void Raft::follower(pb::RaftMessage *m){
    pb::RaftMessage send;
    send.mutable_flags(); // hck
    if(m->IsInitialized())
        send.CopyFrom(*m);

    // got message so increment time
    if(prev_log_size!=log_local.size()){
        srand (time(NULL));
        int rndm = rand() % (TIMER_EXPIRE-HEART_BEAT_INCR);
        timer=timer + HEART_BEAT_INCR + rndm;
        prev_log_size=log_local.size();

        // received vote on me, vote on the one with a higher term than yours
        if(log_local[log_local.size()-1].flags(0)==pb::RaftMessage::CANDIDATE){
            if(current_term<log_local[log_local.size()-1].term()){
                current_term=log_local[log_local.size()-1].term();
                setFlag(&send, pb::RaftMessage::VOTE);
                sendRaftMessage(&send);
                return;
            }
            setFlag(&send, pb::RaftMessage::NO_VOTE);
            sendRaftMessage(&send);
            return;
        }

        // send ACK back
        setFlag(&send, pb::RaftMessage::ACK);
        sendRaftMessage(&send);
        return;
    }
}

/* An election start, special timer start (now when to start again), you send a message vote on me, you already voted on your_self
 * If you got a message back with a higher term than yours, you become follower
 * Got the majority of the votes, you become leader
 * Check what to send back, only send stuff if your state changes!
 * */
void Raft::candidate(pb::RaftMessage *m){
    pb::RaftMessage send;
    send.mutable_flags(); // hck

    if(m->IsInitialized())
        send.CopyFrom(*m);

    // every time a new election start, use a special timer for sending again vote on me message
    if(first_time_candidate){
        first_time_candidate=false;
        vote=1;
        current_term++;
        special_timer=time(nullptr);
        msg_id++;
        send.set_msg_id(msg_id);
        send.set_term(current_term);
        setFlag(&send, pb::RaftMessage::CANDIDATE);
        sendRaftMessage(&send);
        return;
    }

    // special time expired send again vote on me
    if(time_now-special_timer>TIMER_EXPIRE/2){
        first_time_candidate=true;
    }

    // received messages
    // the message has a higher term than you, you become follower
    // someone voted or not voted on you
    if(prev_log_size!=log_local.size()){
        if(current_term <= log_local[log_local.size()-1].term()){
            state=STATES::FOLLOWER;
            vote=0;
            timer=time(nullptr);
            current_term=log_local[log_local.size()-1].term();
            setFlag(&send, pb::RaftMessage::ACK);
            sendRaftMessage(&send);
            return;
        } else if(log_local[log_local.size()-1].flags(0)==pb::RaftMessage::VOTE){
            vote++;
        }else if(log_local[log_local.size()-1].flags(0)==pb::RaftMessage::NO_VOTE){
            not_vote++;
        }

        // you got the majority of the votes/not vote, become leader/follower
        if(vote>=NODES/2){
            state=STATES::LEADER;
            special_timer=time(nullptr);
            vote=0;
            setFlag(&send, pb::RaftMessage::LEADER);
            sendRaftMessage(&send);
            return;
        }else if(not_vote>=NODES/2){
            state=STATES::FOLLOWER;
            timer=time(nullptr);
            vote=0;
            setFlag(&send, pb::RaftMessage::ACK);
            sendRaftMessage(&send);
            return;
        }else if(log_local[log_local.size()-1].flags(0)==pb::RaftMessage::CANDIDATE){
            setFlag(&send, pb::RaftMessage::NO_VOTE);
            sendRaftMessage(&send);
            return;
        }
    }
}

/* He is not a leader anymore if he received a higher term than himself
 * The leader handles what the clients/he wants
 * If the leader receives the majority of the ACK message he can send stuff otherwise repeat previous message (special timer expired)
 * If his queue is empty he still sends a heart beat */
void Raft::leader(pb::RaftMessage *m){
    pb::RaftMessage send;
    send.mutable_flags(); // hck

    if(m->IsInitialized())
        send.CopyFrom(*m);

    // the message has a higher term than you, become a follower
    if(current_term <= log_local[log_local.size()-1].term()){
        state=STATES::FOLLOWER;
        timer=time(0);
        current_term=log_local[log_local.size()-1].term();
        queue_leader.erase(queue_leader.begin(), queue_leader.end());
        setFlag(&send, pb::RaftMessage::ACK);
        sendRaftMessage(&send);
        return;
    }

    // if previous data is received good
    if(is_updated==true && good_ack_back >= NODES/2){
        for(int i=0; i<queue_leader.size()-1; i++){
            if(queue_leader[i].queue_send.sender_ip==my_ip          //  I am the the sender_ip, eraser that from queue
                    && log_local[log_local.size()-1].receiver_ip()==queue_leader[i].queue_send.receiver_ip
                    && log_local[log_local.size()-1].sender_ip() == my_ip){
                queue_leader.erase(queue_leader.begin()+i);
                queue_send_stuf.erase(queue_send_stuf.begin());
                index--;
                is_updated=false;
            }
            if(queue_leader[i].queue_send.receiver_ip==my_ip      // i am  a receiver, add this to my queue update
                    && log_local[log_local.size()-1].receiver_ip()==my_ip
                    && log_local[log_local.size()-1].sender_ip()==queue_leader[i].queue_send.sender_ip){
                queue_update.push_back(log_local[log_local.size()-1]);
                queue_leader.erase(queue_leader.begin()+i);
            }
        }
    }

    // if leader want to send stuff add this also in the queue of the leader
    if(queue_send_stuf.size()!=0){
        QUEUELEADER add_to_queue_leader;
        add_to_queue_leader.queue_send=queue_send_stuf[0];
        add_to_queue_leader.index=index;
        for(int i=0; i<queue_leader.size();i++){
            if(queue_leader[i].queue_send.receiver_ip==my_ip){
                queue_leader[i]=add_to_queue_leader;
                break;
            }else if(i==queue_leader.size()-1 && add_to_queue_leader.queue_send.receiver_ip != queue_leader[i].queue_send.receiver_ip){
                queue_leader.push_back(add_to_queue_leader);
            }
        }
    }

    // leader can send if he has the majority of the ACK back otherwise send again the same message
    time_now=time(0);
    if(good_ack_back >= NODES/2 || time_now-special_timer>TIMER_EXPIRE/2){
        if(time_now-special_timer>TIMER_EXPIRE/2){
            is_updated=false;
        }
        special_timer=time(0);
        good_ack_back=0;
        send.set_msg_id(msg_id);

        // if previous data is received good by the receiver_ip, send to the the sender_ip that data is ok (so sender can eraser that from queue)
        if(log_local[log_local.size()-1].sender_ip() != my_ip
                && log_local[log_local.size()-1].receiver_ip() != my_ip
                && is_updated){
            is_updated=false;
            setFlag(&send, pb::RaftMessage::DATA_OK);
            sendRaftMessage(&send);
            for(int i=0; i<queue_leader.size(); i++){
                if(log_local[log_local.size()-1].sender_ip() == queue_leader[i].queue_send.sender_ip
                        && log_local[log_local.size()-1].receiver_ip() == queue_leader[i].queue_send.receiver_ip)
                    queue_leader.erase(queue_leader.begin()+i);
            }
            return;
        }

        QUEUELEADER add_queue_leader;
        add_queue_leader.index=log_local[log_local.size()-1].index();
        add_queue_leader.queue_send.data=log_local[log_local.size()-1].data();
        add_queue_leader.queue_send.sender_ip=log_local[log_local.size()-1].sender_ip();
        add_queue_leader.queue_send.receiver_ip=log_local[log_local.size()-1].receiver_ip();
    }

    // if queue of the leader is empty, still send heart beat
    if(queue_leader.size()==0){
        setFlag(&send, pb::RaftMessage::NO_CHANGE);
        sendRaftMessage(&send);
        return;
    }else{
        is_updated=true;
        setFlag(&send, pb::RaftMessage::UPDATE);

        // there is one message in queue, send that one
        if(queue_leader.size()==1){
            send.set_sender_ip(queue_leader[0].queue_send.sender_ip);
            send.set_receiver_ip(queue_leader[0].queue_send.receiver_ip);
            send.set_index(queue_leader[0].index);
            send.set_allocated_data(&queue_leader[0].queue_send.data);
            sendRaftMessage(&send);
            return;
        }

        // send message with the highest index
        int highest_index=queue_leader[0].index;
        int j=0;
        for(int i=1; i<queue_leader.size()-1; i++){
            if(highest_index<queue_leader[i].index){
                highest_index=queue_leader[i].index;
                j=i;
            }
        }

        send.set_sender_ip(queue_leader[j].queue_send.sender_ip);
        send.set_receiver_ip(queue_leader[j].queue_send.receiver_ip);
        send.set_index(queue_leader[j].index);
        send.set_allocated_data(&queue_leader[j].queue_send.data);
        sendRaftMessage(&send);
        return;
    }
}

/* handle the states
 * set the data
 * only check the time of the follower*/
void Raft::handleState(){
    time_now=time(0);
    pb::RaftMessage send;

    // set the data
    if(queue_send_stuf.size()>0){
         pb::Message data=queue_send_stuf[0].data;
         data.set_receiver(queue_send_stuf[0].receiver_ip);
         data.set_name(queue_send_stuf[0].sender_ip);

        if(log_local.size() > 0){
            send.CopyFrom(log_local[log_local.size()-1]);
            if(data.IsInitialized()){
                pb::Message *d = send.mutable_data();
                *d = data;
            }

            send.set_index(index);
        }
    }

    if(state==STATES::FOLLOWER){
        checkTimer();
        follower(&send);
    }else if(state==STATES::CANDIDATE){
        candidate(&send);
    }else if(state==STATES::LEADER){
        leader(&send);
    }else{ // error, become follower
        std::cout << "\nError, not a state!";
        state=STATES::FOLLOWER;
        timer=time(0);
        vote=0;
    }
}

/* checks the value of the timer
 * if your time is expires, become candidate */
void Raft::checkTimer(){
    if(time_now-timer > TIMER_EXPIRE){
        state=STATES::CANDIDATE;
        std::cout<<"\nI am expired";
    }
}

/* All messages are stored in a queue (log local)
 * Add to queues if you got a specific message
 * Delete some memory when the queue is to big
 * TODO? if i got to many messages i have to make another function that handles the queue */
void Raft::receivedMessage(pb::RaftMessage *msg){
    pb::RaftMessage new_message = *msg;
    log_local.push_back(new_message);

    // if you got a message with a flag update with you as receiver, add data to the queue update
    if(new_message.flags(0)==pb::RaftMessage::UPDATE && new_message.receiver_ip()==my_ip){
        queue_update.push_back(new_message);
        Message msg_wrapper;

        QHash<int32_t, std::vector<pb::Message>> msgs;
        int32_t q_msg_id = new_message.msg_id();

        for(auto m: queue_update){
            msgs[q_msg_id].push_back(m.data());
        }

        if(msg_wrapper.assembleMessage(&(msgs[q_msg_id]))){
            pb::Message *msg = msg_wrapper.getMessage();
            emit messageReceived(msg);

            // Delete the message from queue_update
            std::vector<size_t> msg_indices;
            for(int i=0; i < queue_update.size(); i++){
                if(queue_update[i].msg_id() == q_msg_id){
                    int indx = i - msg_indices.size(); // Index after the removal of the previous element
                    msg_indices.push_back(indx);
                    queue_update.erase(queue_update.begin() + indx);
                }
            }
        }
    }

    // Your data is send OK, decrease your index and erase what is send OK from the queue
    if(log_local[log_local.size()-1].sender_ip()==my_ip && log_local[log_local.size()-1].flags(0)==pb::RaftMessage::DATA_OK){
        queue_send_stuf.erase(queue_send_stuf.begin());
        index--;
    }

    // if you are a leader and receive a message from a client
    // check how many packets with the same id are received, to know if you got the majority of the ACKs
    // client ask you if you want to update the data to other nodes (index>0) add that in your queue
    if(state==STATES::LEADER){
        if(new_message.msg_id()==msg_id && log_local[log_local.size()-1].flags(0)==pb::RaftMessage::ACK){
            good_ack_back++;
            if(good_ack_back>=NODES/2){
                msg_id++;
            }
        }

        if(log_local[log_local.size()-1].index()>0){
            QUEUELEADER add_queue_leader;
            add_queue_leader.index=log_local[log_local.size()-1].index();
            add_queue_leader.queue_send.data=log_local[log_local.size()-1].data();
            add_queue_leader.queue_send.sender_ip=log_local[log_local.size()-1].sender_ip();
            add_queue_leader.queue_send.receiver_ip=log_local[log_local.size()-1].receiver_ip();
            if(queue_leader.size()<1){									// if the queue of the leader is empty fill the queue
                queue_leader.push_back(add_queue_leader);
            }else{
                for(int i=0; i<queue_leader.size();i++){				// replace an old node with the new index or add it to the queue
                    if(log_local[log_local.size()-1].receiver_ip()==queue_leader[i].queue_send.receiver_ip){
                        queue_leader[i]=add_queue_leader;
                        break;
                    }
                    if(i==queue_leader.size()-1 && log_local[log_local.size()-1].receiver_ip()!=queue_leader[i].queue_send.receiver_ip){
                        queue_leader.push_back(add_queue_leader);
                    }
                }
            }
        }
    }

    // delete some memory from log_local if it is to big
    if(log_local.size()>MAX_SIZE){
        log_local.erase(log_local.begin(), log_local.begin()+MAX_SIZE/2);
    }
}

void Raft::sendMessage(pb::Message *data, std::string receiver_ip){
    /* Split a message if necessary and put in the send queue */
    QUEUESEND send_stuff;

    Message msg_wrapper(data);
    std::vector<pb::Message> split_msgs;
    msg_wrapper.splitForRaft(&split_msgs, 512);

    for(auto m: split_msgs){
        send_stuff.data= m;
        send_stuff.receiver_ip=receiver_ip;
        send_stuff.sender_ip=my_ip;

        queue_send_stuf.push_back(send_stuff);
        index++;
    }
}

void Raft::sendRaftMessage(pb::RaftMessage *raft_msg){
    /* Send a raft message to the router */
    pb::Packet pkt;
    pkt.set_sender_ip(my_ip_int);
    pkt.set_message_type(pb::Packet::RAFT);
    pb::RaftMessage *tmp_msg = pkt.mutable_raft_msg();
    *tmp_msg = *raft_msg;

    router->sendMessage(&pkt);
}

void Raft::setFlag(pb::RaftMessage *msg, pb::RaftMessage::Flags flag){
    // Set the flag of a message
    msg->clear_flags();
    msg->add_flags(flag);
}

void Raft::setRouter(Router *router){
    this->router = router;

    // Connect to router receive signal
    connect(router, &Router::messageReceived, this, &Raft::packetReceived);
}
