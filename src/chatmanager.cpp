#include "chatmanager.h"

ChatManager::ChatManager(Router *r, ChatWindow *w, QObject *parent) : QObject(parent), router(r), chatwindow(w) {
    QSettings settings;

    name = settings.value("name", "Me").toString();
    ip_str = settings.value("ip").toString();
    my_ip = QHostAddress(ip_str).toIPv4Address();
    online = new QHash<quint32, quint32>();

    // Signals
    connect(r, &Router::messageReceived,
             this, &ChatManager::handleMessage);
    connect(w, &ChatWindow::newMessage,
             this, &ChatManager::sendMessage);
    connect(w, &ChatWindow::chatChanged,
             this, &ChatManager::chatChanged);
    connect(w, &ChatWindow::recipientsChanged,
             this, &ChatManager::recipientsChanged);
    connect(w, &ChatWindow::sendFile,
             this, &ChatManager::sendFileAtPath);
    connect(w, &ChatWindow::joinCall,
            this, &ChatManager::joinCall);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout,
            this, &ChatManager::notifyPresence);
    //timer->start(5000);

    // Default Chat recipients for each chat tab:
    recipients = {
        {"192.168.5.1", "192.168.5.2", "192.168.5.3", "192.168.5.4"}
    };

    chatnames = {
        "Group Chat",
    };

    for(int c=0; c<chatnames.size(); c++){
        w->addChat(chatnames[c], false);
    }

    w->goToChat(0);
}

void ChatManager::handleMessage(pb::Packet p) {
    if (p.message_type() == pb::Packet::MESSAGE) {
        pb::Message msg = p.msg();

        QStringList recipients;
        //recipients.append(QHostAddress(p.sender_ip()).toString());
        for(auto ipstr : p.receiver_ip()) {
            recipients.append(QHostAddress(ipstr).toString());
        }
        for(int c=0; c<chatnames.size(); c++){
            if (QString::fromStdString(msg.chatname()) == chatnames[c]){
                recipientsChanged(c, recipients);
                break;
            }
        }

        if(msg.is_file() == true){
            // Prepare download path
            QString download_dir = QDir::homePath() + QDir::separator() + "ChatDownloads";
            QDir dl;
            dl.mkpath(download_dir);
            QFile save_file(download_dir + QDir::separator() + QString::fromStdString(msg.file_name()));

            if (save_file.open(QIODevice::ReadWrite)) {
                save_file.seek(msg.msg_seq());
                save_file.write(msg.data().data(), msg.data().size());
            } else {
                qDebug("Error writing to file");
            }

            if(!msg.more()){
                qDebug("Last packet received");
                QPixmap recvd_image;
                if(recvd_image.load(save_file.fileName())){
                    // If successfully loaded
                    qDebug("Image loaded");
                    QIcon img(recvd_image);

                    // Display to the chat
                    chatwindow->displayImage(
                        QString::fromStdString(msg.chatname()),
                        QString::fromStdString(msg.name()),
                        img,
                        ""
                    );
                } else {
                    qDebug("Invalid image");
                    // Generic file: Save to temp directory
                    chatwindow->writeMessage(
                        QString::fromStdString(msg.chatname()),
                        QString::fromStdString(msg.name()),
                        QString::fromStdString("Sent file `" + QFileInfo(save_file).fileName().toStdString()) + "`.");
                }
            }
        } else {
            // Received text data
            if(msg.name() == name.toUtf8().constData())
                return;

            chatwindow->writeMessage(
                QString::fromStdString(msg.chatname()),
                QString::fromStdString(msg.name()),
                QString::fromStdString(msg.data()));
        }
    } else if (p.message_type() == pb::Packet::PRESENCE) {
        online->insert(p.sender_ip(), 3);
    }
}

void ChatManager::sendMessage(QString chatname, QString message) {
    /* Construct a text message packet and send it to a chat */
    pb::Packet p;
    p.set_message_type(pb::Packet::MESSAGE);
    p.set_sender_ip(my_ip);

    pb::Message *msg = p.mutable_msg();
    msg->set_name(name.toStdString());
    msg->set_data(message.toStdString());

    sendPacket(p, chatname);
}

void ChatManager::sendFile(QString chatname, QByteArray *data, QString filename){
    /* Construct a packet of a file and send it to a chat */
    QFileInfo fi(filename);
    filename = fi.fileName();
    pb::Packet p;
    pb::Message *msg = p.mutable_msg();
    msg->set_more(true);
    int idx = 0;
    int chunksize = 512;
    while(msg->more()) {
        QByteArray section = data->mid(idx, chunksize);

        p.set_message_type(pb::Packet::MESSAGE);
        p.set_sender_ip(my_ip);

        msg->set_data(section.data(), section.size());
        msg->set_file_name(filename.toStdString());
        msg->set_name(name.toStdString());
        msg->set_is_file(true);
        msg->set_msg_seq(idx);
        idx += chunksize;
        msg->set_more(idx < data->size());

        sendPacket(p, chatname);
        QThread::msleep(10);
    }
}

void ChatManager::sendFile(QString chatname, QString filepath){
    /* Convenience method to send a file. Loads the file from a given file path.
     * Determines filetype from extension.
     */
    QFile file(filepath);
    QString filename = file.fileName();

    if (file.open(QIODevice::ReadOnly)){
        QByteArray file_data = file.readAll();
        sendFile(chatname, &file_data, filename);
    }else{
        qDebug() << "Couldn't load file at path: " << filepath;
    }
}

void ChatManager::sendFileAtPath(QString chatname, QString filepath){
    /* Used to connect a signal to the overloaded sendFile */
    sendFile(chatname, filepath);
}

void ChatManager::sendPacket(pb::Packet p, QString chatname){
    /* Send a packet to the specified chat */
    pb::Message *msg = p.mutable_msg();

    for(int c=0; c<chatnames.size(); c++){
        if (chatname == chatnames[c]){
            for(auto r: recipients[c]){
                p.add_receiver_ip(QHostAddress(r).toIPv4Address());
            }

            msg->set_chatname(chatname.toUtf8().constData());
            router->sendMessage(p);
            break;
        }
    }
}

void ChatManager::joinCall() {
    Voip *v = new Voip();
    connect(v, &Voip::sendAudio,
            router, &Router::sendMessage);
    connect(router, &Router::messageReceived,
            v, &Voip::processPendingMessage);
}

void ChatManager::notifyPresence() {
    pb::Packet p;
    p.set_message_type(pb::Packet::PRESENCE);
    p.set_sender_ip(my_ip);
    router->sendMessage(p);
    
    QMutableHashIterator<quint32, quint32> i(*online);
    while (i.hasNext()) {
        i.next();
        i.setValue(i.value()-1);
        if(i.value() == 0) i.remove();
    }
    emit isOnline(online->keys());
}

void ChatManager::chatChanged(int chatindex, StateChange change){
    /* Signal received that a chat status has changed */
    std::vector<QString> current_chat_names = chatwindow->getChatNames();
    std::vector<QString> default_vec = {"192.168.5.1", "192.168.5.2", "192.168.5.3", "192.168.5.4"};

    switch(change){
        case CREATED:
            qDebug() << "Chat Created: " << current_chat_names[chatindex] << "\n";
            recipients.push_back(default_vec);
            chatnames.push_back(current_chat_names[chatindex]);
            break;
        case RENAMED:
            qDebug() << "Chat `" << chatnames[chatindex] << "` ";
            chatnames[chatindex] = current_chat_names[chatindex];
            qDebug() << "renamed to " << current_chat_names[chatindex] << "\n";
            break;
        case DELETED:
            qDebug() << "Deleted Chat " << chatnames[chatindex] << "\n";
            chatnames.erase(chatnames.begin() + chatindex);
            recipients.erase(recipients.begin() + chatindex);
            break;
    }
}

void ChatManager::recipientsChanged(int chatindex, QStringList new_rcpnts){
    /* Signal received that the recipients of a chat changed */
    std::vector<QString> new_recipients;

    qDebug() << "Changed recipients of " << chatnames[chatindex] << " to ";

    for(QString ipstr : new_rcpnts){ // Remove all spaces
        new_recipients.push_back(ipstr.trimmed());
        qDebug() << ipstr.trimmed();
    }

    recipients[chatindex] = new_recipients;
}
