#include <QtWidgets>
#include <QtNetwork>

class Transceiver : public QObject {
    Q_OBJECT

public:
    explicit Transceiver(QObject *parent = 0);
        
public slots:
    void sendMessage(QByteArray data);
    void processPendingDatagrams();
signals:
    void messageReceived(QByteArray data);

private:
    QHostAddress groupAddress;
    QUdpSocket *udpSocket;
};
