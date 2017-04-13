#pragma once

#include <QMainWindow>
#include <QString> 
#include <QHash>
#include <QMenuBar>
#include <QMenu>
#include <QInputDialog>
#include <QKeySequence>

#include "chatpanel.h"

enum StateChange{
    CREATED,
    DELETED,
    RENAMED
};

class ChatWindow : public QMainWindow {
    Q_OBJECT

public:
    ChatWindow(QWidget *parent = 0);
    //~ChatWindow();

public slots:
    void addChat(QString name, bool emit_signal);
    void addChat(QString name);
    void writeMessage(QString chatname, QString sender, QString message);

    void newChatSetup();
    void removeChat();
    void editChat();
    void goToChat(int indx);
    void editChatRecipients();
    std::vector<QString> getChatNames();

signals:
    void newMessage(QString chatname, QString message);
    void chatChanged(int chatindex, StateChange change);
    void recipientsChanged(int chatindex, std::string recipients);

private:
    QTabWidget *tabs;
    QHash<QString, ChatPanel*> *chats;

    // Menu Bar
    QMenu *chatMenu;
    QAction *newChatAction;
    QAction *deleteChatAction;
    QAction *editChatAction;
    QAction *editChatRcpntsAction;
};
