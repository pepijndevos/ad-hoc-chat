#include "chatpanel.h"
#include <QGridLayout> 

ChatPanel::ChatPanel(QString name, QWidget *parent) : QWidget(parent), chatName(name) {
    QGridLayout *layout = new QGridLayout();

    chat = new QListWidget();
    layout->addWidget(chat, 0, 0, 1, 3);
    btn = new QPushButton("Send!");
    layout->addWidget(btn, 1, 1);
    file_btn = new QPushButton("Send File...");
    layout->addWidget(file_btn, 1, 2);
    txt = new QLineEdit();
    layout->addWidget(txt, 1, 0);

    setLayout(layout);

    connect(btn, &QPushButton::clicked,
            this, &ChatPanel::sendMessage);
    connect(file_btn, &QPushButton::clicked,
            this, &ChatPanel::selectFile);
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
    if(txt->text().trimmed().isEmpty())
        return;

    emit newMessage(chatName, txt->text());
    writeMessage("Me", txt->text());
    txt->clear();
}

void ChatPanel::selectFile() {
    /* Open file dialog to select a file */
    QString file_path = QFileDialog::getOpenFileName(0,
        tr("Send File"), QDir::homePath(),
        tr("Files (*);;Image files (*.png *.jpg);;Video files (*.avi *.mp4 *.mov *.gif *.mpg *.mpeg)"));

    if(!file_path.isEmpty()){
        emit sendFile(chatName, file_path);
    }
}

void ChatPanel::setIconSize(QSize size){
    /* Set the panel's icon size*/
    chat->setIconSize(size);
}
