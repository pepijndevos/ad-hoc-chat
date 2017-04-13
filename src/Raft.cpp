/*
 * Raft.cpp
 *
 *  Created on: 11 apr. 2017
 *      Author: Antonis Katzourakis & Eva Knol
 group: 3
 */

#include "Raft.h"

Raft::Raft() :
    state("Follower"),
    timer(0),
    time_now(0),
    first_time_candidate(false),
    special_timer(0),
    prev_log_size(0),
    vote(0),
    current_term(0),
    first_time(true),
    index(0),
    not_vote(0),
    msg_id(0),
    good_ack_back(0),
    leader_can_send(false){
}

Raft::~Raft() {
}

/* Increment time if you got a message
 * Check what to send back
 * Send current term, a flag, my ip, data (first one that is in my queue or zero), my index value (how big my queue send stuff is), send message id from previous one
 *  */
void Raft::follower(std::string my_ip){
    msg_id=log_local[log_local.size()-1].msg_id();

    // got message so increment time
    if(prev_log_size!=log_local.size()){
        timer=timer + HEART_BEAT_INCR;

        // received vote on me, vote on the one with a higher term than yours
        if(log_local[log_local.size()-1].flags(0)==pb::RaftMessage::CANDIDATE){
            if(current_term<log_local[log_local.size()-1].term()){
                current_term=log_local[log_local.size()-1].term();
                sendMessage(current_term, pb::RaftMessage::VOTE, my_ip, data, index, msg_id);
                return;
            }
            sendMessage(current_term, pb::RaftMessage::NO_VOTE, my_ip, data, index, msg_id);
            return;
        }

        // Your data is send OK, decrease your index and erase what is send OK from the queue
        if(log_local[log_local.size()-1].receiver_ip()==my_ip && log_local[log_local.size()-1].flags(0)==pb::RaftMessage::DATA_OK){
            queue_send_stuf.erase(queue_send_stuf.begin());
            index--;
        }

        // send ACK back
        sendMessage(current_term, pb::RaftMessage::ACK, my_ip, data, index, msg_id);
        return;
    }
}

/* An election start, special timer start (now when to start again), you send a message vote on me, you already voted on your_self
 * If you got a message back with a higher term than yours, you become follower
 * Got the majority of the votes, you become leader
 * Check what to send back, only send stuff if your state changes!
 * */
void Raft::candidate(std::string my_ip){

    // every time a new election start, use a special timer for sending again vote on me message
    if(!first_time_candidate){
        vote=1;
        current_term++;
        special_timer=time(nullptr);
        msg_id++;
        sendMessage(current_term, pb::RaftMessage::CANDIDATE,my_ip, data, index, msg_id);
        return;
    }

    // special time expired send again vote on me
    if(time_now-special_timer>TIMER_EXPIRE/4){
        first_time_candidate=false;
    }

    // received messages
    // the message has a higher term than you, you become follower
    // someone voted or not voted on you
    if(prev_log_size!=log_local.size()){
        if(current_term <= log_local[log_local.size()-1].term()){
            state="Follower";
            vote=0;
            timer=time(nullptr);
            sendMessage(current_term, pb::RaftMessage::ACK, my_ip, data, index, msg_id);
            return;
        } else 	if(log_local[log_local.size()-1].flags(0)==pb::RaftMessage::VOTE){
            vote++;
        }else if(log_local[log_local.size()-1].flags(0)==pb::RaftMessage::NO_VOTE){
            not_vote++;
        }

        // you got the majority of the votes/not vote, become leader/follower
        if(vote>=NODES/2){
            state="Leader";
            special_timer=time(nullptr);
            vote=0;
            sendMessage(current_term, pb::RaftMessage::LEADER, my_ip, data, index, msg_id);
            return;
        }else if(not_vote>=NODES/2){
            state="Follower";
            timer=time(nullptr);
            vote=0;
            sendMessage(current_term, pb::RaftMessage::ACK, my_ip, data, index, msg_id);
            return;
        }
    }
}

/* He is not a leader anymore if he received a higher term than himself
 * The leader handles what the clients/he wants
 * If the leader receives the majority of the ACK message he can send stuff otherwise repeat previous message (special timer expired)
 * If his queue is empty he still sends a heart beat */
void Raft::leader(std::string my_ip){

    // the message has a higher term than you, become a follower
    if(current_term <= log_local[log_local.size()-1].term()){
        state="Follower";
        timer=time(0);
        queue_leader.erase(queue_leader.begin(), queue_leader.end());
        sendMessage(current_term, pb::RaftMessage::ACK, my_ip, data, index, msg_id);
        return;
    }

    // if leader want to send stuff add this also in the queue of the leader
    if(queue_send_stuf.size()!=0){
        QueueLeader add_to_queue_leader;
        add_to_queue_leader.index=index;
        add_to_queue_leader.data=queue_send_stuf[0];
        add_to_queue_leader.receiver_ip=my_ip;
        for(int i=0; i<queue_leader.size();i++){
            if(queue_leader[i].receiver_ip==my_ip){
                queue_leader[i]=add_to_queue_leader;
                break;
            }else if(i==queue_leader.size()-1 && add_to_queue_leader.receiver_ip!=queue_leader[i].receiver_ip){
                queue_leader.push_back(add_to_queue_leader);
            }
        }
    }

    // leader can send if he has the majority of the ACK back otherwise send again the same message
    time_now=time(0);
    if(leader_can_send==true || time_now-special_timer>TIMER_EXPIRE/4){
        special_timer=time(0);
        good_ack_back=0;

        // if queue of the leader is empty, still send heart beat
        if(queue_leader.size()==0){
            sendMessage(current_term, pb::RaftMessage::NO_CHANGE, my_ip, data, 0, msg_id);
            return;
        }else{  // set the data
            data.set_name(my_ip);
            data.set_receiver(queue_leader[0].receiver_ip);
            data.set_data(queue_leader[0].data);
        }

        // there is one message in queue, send that one
        if(queue_leader.size()==1){
            sendMessage(current_term, pb::RaftMessage::UPDATE, queue_leader[0].receiver_ip, data, queue_leader[0].index, msg_id);
            queue_update.push_back(queue_leader[0].data);
            return;
        }

        // send message with the highest index
        int highest_index=queue_leader[0].index;
        int j=0;
        for(int i=1; i<queue_leader.size(); i++){
            if(highest_index<queue_leader[i].index){
                highest_index=queue_leader[i].index;
                j=i;
            }
        }
        data.set_name(queue_leader[j].name());
        data.set_receiver(quequeue_leader[j].receiver());
        data.set_text(queue_leader[j].text());
        data.set_file_data(queue_leader[j].file_data());
        sendMessage(current_term, pb::RaftMessage::UPDATE, queue_leader[j].receiver_ip, data, queue_leader[j].index, msg_id);
        queue_update.push_back(queue_leader[0].data);
        return;
    }
}

/* handle the states
 * set the data
 * only check the time of the follower*/
void Raft::handleState(std::string my_ip){
    time_now=time(0);

    // set the data
    data.set_name("000");
    data.set_receiver("000");
    data.set_text("000");
    data.set_file_data("000");
    if(queue_send_stuf.size()>0){
        data.set_name(queue_send_stuf[0].name());
        data.set_receiver(queue_send_stuf[0].receiver());
        data.set_text(queue_send_stuf[0].text());
        data.set_file_data(queue_send_stuf[0].file_data());
    }

    if(state=="Follower"){
        checkTimer();
        follower(my_ip);
    }else if(state=="Candidate"){
        candidate(my_ip);
    }else if(state=="Leader"){
        leader(my_ip);
    }else{ // error, become follower
        std::cout << "\nError, not a state!";
        state="Follower";
        timer=time(0);
        vote=0;
    }
}

/* checks the value of the timer
 * if your time is expires, become candidate */
void Raft::checkTimer(){
    if(time_now-timer > TIMER_EXPIRE){
        state="Candidate";
        std::cout<<"\nI am expired";
    }
}

/* All messages are stored in a queue (log local)
 * Add to queues if you got a specific message
 * Delete some memory when the queue is to big
 * TODO? if i got to many messages i have to make another function that handles the queue */
void Raft::receivedMessage(pb::RaftMessage new_message){
    log_local.push_back(new_message);

    // if you got a message with a flag update, add data to the queue update
    if(new_message.flags==pb::RaftMessage::UPDATE){
        queue_update.push_back(new_message.data);				//TODO
    }

    // if you are a leader and receive a message from a client
    // check how many packets with the same id are received, to know if you got the majority of the ACKs
    // client ask you if you want to update the data to other nodes (index>0) add that in your queue
    if(state=="Leader"){
        if(new_message.msg_id==msg_id){
            good_ack_back++;
            if(good_ack_back==NODES/2){
                msg_id++;
                good_ack_back=0;
                leader_can_send=true;
            }
        }
        if(log_local[log_local.size()-1].index>0){
            QueueLeader add_to_queue_leader;
            add_to_queue_leader.index=log_local[log_local.size()-1].index;
            add_to_queue_leader.data=log_local[log_local.size()-1].data;
            add_to_queue_leader.receiver_ip=log_local[log_local.size()-1].receiver_ip;
            if(queue_leader.size()<1){									// if the queue of the leader is empty fill the queue
                queue_leader.push_back(add_to_queue_leader);
            }else{
                for(int i=0; i<queue_leader.size();i++){				// replace an old node with the new index or add it to the queue
                    if(add_to_queue_leader.receiver_ip==queue_leader[i].receiver_ip){
                        queue_leader[i]=add_to_queue_leader;
                        break;
                    }
                    if(i==queue_leader.size()-1 && add_to_queue_leader.receiver_ip!=queue_leader[i].receiver_ip){
                        queue_leader.push_back(add_to_queue_leader);
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

/* I want to send stuff, put this in my queue */
void Raft::iWantToSendStuff(pb::Message data){
    queue_send_stuf.push_back(data);
    index++;
}

/* send the message */
void Raft::sendMessage(int current_term, pb::RaftMessage::Flags flag, std::string receiver_ip, pb::Message data, int index, int msg_id){
    pb::RaftMessage	send_message;
    send_message.term(current_term);
    send_message.add_flag(f);
    send_message.receiver_ip(receiver_ip);
    send_message.data(data);
    send_message.index(index);
    send_message.msg_id(msg_id);
    //TODO
}

