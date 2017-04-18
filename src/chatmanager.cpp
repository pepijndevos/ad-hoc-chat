#include "chatmanager.h"

ChatManager::ChatManager(Router *r, ChatWindow *w, QObject *parent) : QObject(parent), router(r), chatwindow(w) {
    QSettings settings;

    name = settings.value("name", "Me").toString();
    ip_str = settings.value("ip").toString();
    my_ip = QHostAddress(ip_str).toIPv4Address();
    online = new QHash<quint32, quint32>();

    // Signals
    QObject::connect(r, &Router::messageReceived,
                     this, &ChatManager::handleMessage);
    QObject::connect(w, &ChatWindow::newMessage,
                     this, &ChatManager::sendMessage);
    QObject::connect(w, &ChatWindow::chatChanged,
                     this, &ChatManager::chatChanged);
    QObject::connect(w, &ChatWindow::recipientsChanged,
                     this, &ChatManager::recipientsChanged);
    QObject::connect(w, &ChatWindow::sendFile,
                     this, &ChatManager::sendFileAtPath);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout,
            this, &ChatManager::notifyPresence);
    timer->start(5000);

    // Default Chat recipients for each chat tab:
    recipients = {
        {"192.168.5.1", "192.168.5.2", "192.168.5.3", "192.168.5.4"},
        {"192.168.5.1"},
        {"192.168.5.2"},
        {"192.168.5.3"},
        {"192.168.5.4"}
    };

    chatnames = {
        "Group Chat",
        "Hessel",
        "Eva",
        "Antonis",
        "Pepijn"
    };

    int rmv = -1;
    for(int c=0; c<chatnames.size(); c++){
        if (chatnames[c] == name){
            rmv = c;
            continue;
        }
        w->addChat(chatnames[c], false);
    }

    if (rmv >= 0){ // Remove the chat to myself
        recipients.erase(recipients.begin() + rmv);
        chatnames.erase(chatnames.begin() + rmv);
    }

    w->goToChat(0);
}

void ChatManager::handleMessage(pb::Packet p) {
    if (p.message_type() == pb::Packet::MESSAGE) {
        pb::Message msg = p.msg();

        if(msg.is_file() == true){
            // TODO:
            //   1) For now, it assumes it is an image or a generic filetype
            //       with an empty caption.
            //   2) Support retina displays (images are pixelated)
            //

            bool no_dl_flag = false;            // Don't download data you send.
            if(msg.name() == name.toUtf8().constData()){
                msg.set_name("Me");
                no_dl_flag = true;
            }

            // Prepare download path
            QString download_dir = QDir::homePath() + QDir::separator() + "ChatDownloads";
            QDir dl;
            dl.mkpath(download_dir);
            QFile save_file(download_dir + QDir::separator() + QString::fromStdString(msg.file_name()));

            std::string filetype;
            switch(utils::getFiletype(QString::fromStdString(msg.file_name()))){
                case Filetypes::JPG:
                    filetype = "JPG";
                    break;
                case Filetypes::PNG:
                    filetype = "PNG";
                    break;
                default: // Default to GENERIC
                    filetype = "GENERIC";
                    break;
            }

            QByteArray byte_array(&(msg.data())[0u], msg.data().length());

            if(filetype == "PNG" || filetype == "JPG"){
                QPixmap recvd_image;
                if(recvd_image.loadFromData(byte_array, filetype.c_str())){
                    // If successfully loaded
                    QIcon img(recvd_image);

                    // Save image
                    if(!no_dl_flag)
                        recvd_image.save(save_file.fileName(), filetype.c_str());

                    // Display to the chat
                    chatwindow->displayImage(
                        QString::fromStdString(msg.chatname()),
                        QString::fromStdString(msg.name()),
                        img,
                        ""
                    );
                 }
            } else {
                // Generic file: Save to temp directory
                if (save_file.open(QIODevice::ReadWrite)) {
                    if(!no_dl_flag)
                        save_file.write(byte_array);

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
    pb::Packet p;
    QFileInfo fi(filename);
    filename = fi.fileName();

    p.set_message_type(pb::Packet::MESSAGE);
    p.set_sender_ip(my_ip);

    pb::Message *msg = p.mutable_msg();
    msg->set_data(data->toStdString());
    msg->set_file_name(filename.toStdString());
    msg->set_name(name.toStdString());
    msg->set_is_file(true);

    sendPacket(p, chatname);
}

void ChatManager::sendFile(QString chatname, QString filepath){
    /* Convenience method to send a file. Loads the file from a given file path.
     * Determines filetype from extension.
     */
    QFile file(filepath);
    QString filename = file.fileName();
    Filetypes filetype = utils::getFiletype(filename);

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

void ChatManager::recipientsChanged(int chatindex, std::string new_rcpnts){
    /* Signal received that the recipients of a chat changed */
    std::vector<QString> new_recipients;

    std::vector<std::string> x = utils::split(new_rcpnts, ',');
    qDebug() << "Changed recipients of " << chatnames[chatindex] << " to ";

    for(int r=0; r < x.size(); r++){ // Remove all spaces
        new_recipients.push_back(QString::fromStdString(x[r]).trimmed());
        qDebug() << new_recipients[r] << "\n";
    }

    recipients[chatindex] = new_recipients;
}
