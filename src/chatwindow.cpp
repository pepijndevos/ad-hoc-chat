#include "chatwindow.h"

#include <QTabWidget>
#include <QGridLayout> 
#include <QLineEdit> 
#include <QPushButton> 
#include <QVBoxLayout> 
#include <QLabel> 

ChatWindow::ChatWindow(QWidget *parent) : QMainWindow(parent) {
    QTabWidget *tabs = new QTabWidget(this);

    QWidget *panel = new QWidget();
    QGridLayout *layout = new QGridLayout();

    QWidget *chat = new QWidget();
    QVBoxLayout *chat_layout = new QVBoxLayout();
    chat_layout->addWidget(new QLabel("User 1: Hello world."));
    chat_layout->addWidget(new QLabel("User 2: How are you?"));
    chat_layout->addWidget(new QLabel("User 3: Good, good"));
    chat->setLayout(chat_layout);

    layout->addWidget(chat, 0, 0, 1, 2);
    //layout->addWidget(new QPushButton("Magic"), 0, 0, 1, 2);
    layout->addWidget(new QPushButton("Send!"), 1, 1);
    layout->addWidget(new QLineEdit("Hello world"), 1, 0);
    
    panel->setLayout(layout);

    tabs->addTab(panel, "User 1");
    tabs->addTab(new QWidget(), "User 2");
    tabs->addTab(new QWidget(), "User 3");
    tabs->addTab(new QWidget(), "User 4");
    tabs->addTab(new QWidget(), "Group Chat");
    setCentralWidget(tabs);
}
