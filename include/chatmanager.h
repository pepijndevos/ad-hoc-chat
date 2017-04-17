#include <QObject>
#include <QHash>
#include <QDebug>
#include <QString>
#include <QMutableHashIterator>

#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>

#include "chatwindow.h"
#include "router.h"

class ChatManager : public QObject {
    Q_OBJECT

public:
    explicit ChatManager(Router *r, ChatWindow *w, QObject *parent = 0);

public slots:
    void handleMessage(pb::Packet p);
    void sendPacket(pb::Packet p, QString chatname);
    void sendMessage(QString chatname, QString message);
    void sendFile(QString chatname, QByteArray *data, pb::Message::Filetype filetype);
    void sendFile(QString chatname, QString filepath);

    void notifyPresence();
    void chatChanged(int chatindex, StateChange change);
    void recipientsChanged(int chatindex, std::string new_rcpnts);

private slots:
    void sendFileAtPath(QString chatname, QString filepath);

signals:
    void isOnline(QList<quint32> online);

private:
    Router* router;
    ChatWindow *chatwindow;
    quint32 my_ip;
    QString ip_str;
    QString name;
    QHash<quint32, quint32> *online;

    // Recipients & Chat names
    std::vector<std::vector<QString>> recipients;
    std::vector<QString> chatnames;
};
