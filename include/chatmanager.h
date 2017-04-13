#include <QObject>
#include <QHash>
#include "chatwindow.h"
#include "router.h"

class ChatManager : public QObject {
    Q_OBJECT

public:
    explicit ChatManager(Router *r, ChatWindow *w, QObject *parent = 0);

public slots:
    void handleMessage(pb::Packet p);
    void sendMessage(QString chatname, QString message);
    void notifyPresence();

signals:
    void isOnline(QList<quint32> online);

private:
    Router* router;
    ChatWindow *chatwindow;
    quint32 my_ip;
    QString ip_str;
    QString name;
    QHash<quint32, quint32> *online;
};
