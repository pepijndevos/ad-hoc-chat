#include <QObject>
#include "transceiver.h"

class Router : public QObject {
    Q_OBJECT

public:
    explicit Router(Transceiver *t, QObject *parent = 0);

public slots:
    void sendMessage(pb::Packet);
    void routeMessage(pb::Packet);

signals:
    void messageReceived(pb::Packet);

private:
    void handleAck(pb::Packet);
    void flood(pb::Packet);
    unsigned int sequence_number;
    Transceiver *transceiver;
};
