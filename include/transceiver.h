#ifndef TRANSCEIVER_H_
#define TRANSCEIVER_H_

#include <QtWidgets>
#include <QtNetwork>
#include "Packet.pb.h"

#include "cryptopp/cryptlib.h"
#include "cryptopp/filters.h"
#include "cryptopp/files.h"
#include "cryptopp/modes.h"
#include "cryptopp/hex.h"
#include "cryptopp/aes.h"

using namespace CryptoPP;

class Transceiver : public QObject {
    Q_OBJECT

public:
    explicit Transceiver(QObject *parent = 0);

public slots:
    void sendMessage(pb::Packet);
    void processPendingDatagrams();
signals:
    void messageReceived(pb::Packet);

private:
    QHostAddress groupAddress;
    QUdpSocket *udpSocket;

    char key[AES::MAX_KEYLENGTH] = "super secret";
    char iv[AES::BLOCKSIZE] = "cheese";
};

#endif // TRANSCEIVER_H_
