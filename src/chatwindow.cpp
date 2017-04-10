#include "chatwindow.h"

#include <QTabWidget>

ChatWindow::ChatWindow(QWidget *parent) : QMainWindow(parent) {
    tabs = new QTabWidget(this);
    chats = new QHash<QString, ChatPanel*>();

    setCentralWidget(tabs);
}

void ChatWindow::addChat(QString name) {
    ChatPanel *panel = new ChatPanel();
    chats->insert(name, panel);
    tabs->addTab(panel, name);
}

void ChatWindow::writeMessage(QString chatname, QString sender, QString message) {
    chats->value(chatname)->writeMessage(sender, message);
}
