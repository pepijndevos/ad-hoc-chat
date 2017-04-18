#include <QtNetwork>
#include <QtMultimedia>

class Voip : public QObject {
    Q_OBJECT

public:
    explicit Voip(QObject *parent = 0);


private slots:
    void handleStateChanged(QAudio::State);
    void processPendingDatagrams();
    void processPendingAudio();

private:
    QHostAddress groupAddress;
    QHostAddress my_ip;
    QAudioInput* audioIn;
    QAudioOutput* audioOut;
    QIODevice *outbuf;
    QIODevice *inbuf;
    QUdpSocket *udpSocket;
};
