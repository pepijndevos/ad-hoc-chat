#include <QMainWindow>
#include <QString> 
#include <QHash>

#include "chatpanel.h"

class ChatWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit ChatWindow(QWidget *parent = 0);
    //~ChatWindow();

public slots:
    void addChat(QString name);
    void writeMessage(QString chatname, QString sender, QString message);

signals:
    void newMessage(QString chatname, QString message);

private:
    QTabWidget *tabs;
    QHash<QString, ChatPanel*> *chats;
};
