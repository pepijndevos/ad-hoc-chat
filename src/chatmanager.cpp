#include "chatmanager.h"

ChatManager::ChatManager(Router *r, ChatWindow *w, QObject *parent) : QObject(parent), router(r), chatwindow(w) {
    QSettings settings;
    name = settings.value("name", "Me").toString();
    ip_str = settings.value("ip").toString();
    my_ip = QHostAddress(ip_str).toIPv4Address();

    QObject::connect(r, &Router::messageReceived,
                     this, &ChatManager::handleMessage);
    QObject::connect(w, &ChatWindow::newMessage,
                     this, &ChatManager::sendMessage);

    w->addChat("Group Chat");
    w->addChat("192.168.5.1");
    w->addChat("192.168.5.2");
    w->addChat("192.168.5.3");
    w->addChat("192.168.5.4");
}


void ChatManager::handleMessage(pb::Packet p) {
    if (p.message_type() == pb::Packet::MESSAGE) {
        pb::Message msg = p.msg();
        chatwindow->writeMessage(
            QString::fromStdString(msg.chatname()),
            QString::fromStdString(msg.name()),
            QString::fromStdString(msg.data()));
    }
}

void ChatManager::sendMessage(QString chatname, QString message) {
    pb::Packet p;
    p.set_message_type(pb::Packet::MESSAGE);
    p.set_sender_ip(my_ip);

    pb::Message *msg = p.mutable_msg();
    msg->set_name(name.toStdString());
    msg->set_data(message.toStdString());

    if (chatname == "Group Chat") {
        msg->set_chatname("Group Chat");
        p.add_receiver_ip(QHostAddress("192.168.5.1").toIPv4Address());
        p.add_receiver_ip(QHostAddress("192.168.5.2").toIPv4Address());
        p.add_receiver_ip(QHostAddress("192.168.5.3").toIPv4Address());
        p.add_receiver_ip(QHostAddress("192.168.5.4").toIPv4Address());
    } else {
        msg->set_chatname(ip_str.toStdString());
        p.add_receiver_ip(QHostAddress(chatname).toIPv4Address());
    }
    router->sendMessage(p);
}

