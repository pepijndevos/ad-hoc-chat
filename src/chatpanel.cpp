#include "chatpanel.h"
#include <QGridLayout> 

ChatPanel::ChatPanel(QString name, QWidget *parent) : QWidget(parent), chatName(name) {
    QGridLayout *layout = new QGridLayout();

    chat = new QListWidget();
    layout->addWidget(chat, 0, 0, 1, 2);
    btn = new QPushButton("Send!");
    layout->addWidget(btn, 1, 1);
    txt = new QLineEdit();
    layout->addWidget(txt, 1, 0);

    setLayout(layout);

    connect(btn, &QPushButton::clicked,
            this, &ChatPanel::sendMessage);
    connect(txt, &QLineEdit::returnPressed,
            this, &ChatPanel::sendMessage);
}

void ChatPanel::writeMessage(QString sender, QString message) {
    QString label = QString("%1: %2").arg(sender, message);
    new QListWidgetItem(label, chat);
    chat->scrollToBottom();
}

void ChatPanel::displayImage(QString sender, QIcon image, QString caption){
    QString label = QString("%1:").arg(sender);
    new QListWidgetItem(label, chat);
    new QListWidgetItem(image, NULL, chat);
    new QListWidgetItem(caption, chat);
    chat->scrollToBottom();
}

void ChatPanel::sendMessage() {
    emit newMessage(chatName, txt->text());
    writeMessage("Me", txt->text());
    txt->clear();
}

void ChatPanel::setIconSize(QSize size){
    /* Set the panel's icon size*/
    chat->setIconSize(size);
}
