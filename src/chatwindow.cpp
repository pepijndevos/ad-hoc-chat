#include "chatwindow.h"

ChatWindow::ChatWindow(QWidget *parent) : QMainWindow(parent) {
    tabs = new QTabWidget(this);
    chats = new QHash<QString, ChatPanel*>();

    // Menu Bar
    chatMenu = new QMenu("Chat");

    // New Chat
    newChatAction = chatMenu->addAction("Add new Chat");
    newChatAction->setShortcuts(QKeySequence::New);
    newChatAction->setStatusTip("Create a new chat");
    connect(newChatAction, &QAction::triggered, this, &ChatWindow::newChatSetup);

    // Edit Chat name
    editChatAction = chatMenu->addAction("Edit Chat name");
    QKeySequence CtrlR = QKeySequence(Qt::CTRL + Qt::Key_R);
    editChatAction->setShortcut(CtrlR);
    editChatAction->setStatusTip("Edit chat name");
    connect(editChatAction, &QAction::triggered, this, &ChatWindow::editChat);

    // Edit Chat recipients
    editChatRcpntsAction = chatMenu->addAction("Edit Chat members");
    QKeySequence CtrlE = QKeySequence(Qt::CTRL + Qt::Key_E);
    editChatRcpntsAction->setShortcut(CtrlE);
    editChatRcpntsAction->setStatusTip("Edit chat members");
    connect(editChatRcpntsAction, &QAction::triggered, this, &ChatWindow::editChatRecipients);

    // Delete Chat
    deleteChatAction = chatMenu->addAction("Delete Chat");
    deleteChatAction->setStatusTip("Delete this chat");
    connect(deleteChatAction, &QAction::triggered, this, &ChatWindow::removeChat);

    menuBar()->addMenu(chatMenu);
    setCentralWidget(tabs);
}

void ChatWindow::addChat(QString name, bool emit_signal){
    /* Add a chat and notify the Chat manager */
    ChatPanel *panel = new ChatPanel(name, this);
    connect(panel, &ChatPanel::newMessage,
            this, &ChatWindow::newMessage);

    connect(panel, &ChatPanel::sendFile,
            this, &ChatWindow::sendFile);

    chats->insert(name, panel);
    tabs->addTab(panel, name);

    if (emit_signal)
        emit chatChanged(tabs->count()-1, CREATED);
}

void ChatWindow::addChat(QString name){
    /* Helper function to add a chat with signal emission */
    addChat(name, true);
}

void ChatWindow::newChatSetup(){
    /* Add a new chat */
    addChat("New Chat");
    tabs->setCurrentIndex(tabs->count() - 1);
}

void ChatWindow::goToChat(int indx){
    if (indx < tabs->count())
        tabs->setCurrentIndex(indx);
}

void ChatWindow::removeChat(){
    /* Remove the current chat */
    emit chatChanged(tabs->currentIndex(), DELETED);
    tabs->removeTab(tabs->currentIndex());
}

void ChatWindow::editChat(){
    /* Open a dialog to enter a new chat name */
    int current_chat = tabs->currentIndex();
    QString current_name = tabs->tabText(current_chat);
    bool ok;

    QString chat_name = QInputDialog::getText(this, tr("Edit Chat Name"), tr("Chat name:"), QLineEdit::Normal, current_name, &ok);
    if(ok && !chat_name.isEmpty()){
        tabs->setTabText(current_chat, chat_name);
        emit chatChanged(current_chat, RENAMED);
    }
}

void ChatWindow::editChatRecipients(){
    /* Open a dialog to edit recipients */
    int current_chat = tabs->currentIndex();

    bool ok;
    QString recipients = QInputDialog::getText(this, tr("Edit Chat Recipients"), tr("Comma-separated IPs:"), QLineEdit::Normal, "", &ok);
    if(ok && !recipients.isEmpty()){
        emit recipientsChanged(current_chat, recipients.toUtf8().constData());
    }
}

std::vector<QString> ChatWindow::getChatNames(){
    std::vector<QString> names;
    for(int t=0; t<tabs->count(); t++){
        names.push_back(tabs->tabText(t));
    }

    return names;
}

void ChatWindow::setChatIconSizes(QSize size){
    /* Set the default icon size of each chat panel */
    QHash<QString, ChatPanel*>::iterator c;
    for (c = chats->begin(); c != chats->end(); ++c){
        c.value()->setIconSize(size);
    }
}

void ChatWindow::writeMessage(QString chatname, QString sender, QString message) {
    /* Add a received/sent message to the specified chat */
    chats->value(chatname)->writeMessage(sender, message);
}

void ChatWindow::displayImage(QString chatname, QString sender, QIcon image, QString caption){
    /* Display a received/sent image to the specified chat */
    chats->value(chatname)->displayImage(sender, image, caption);
}

void ChatWindow::setWindowSize(float p=0.5){
    /* Set the window size using the percentage of the screen */
    resize(QDesktopWidget().availableGeometry(this).size() * p);
}
