#include <QtNetwork>
#include <QtMultimedia>

class Voip : public QObject {
    Q_OBJECT

public:
    explicit Voip(QObject *parent = 0);

public slots:
    void call(quint32 ip);

private slots:
    void handleStateChanged(QAudio::State);
    void processPendingDatagrams();

private:
    QHostAddress groupAddress;
    QAudioInput* audioIn;
    QAudioOutput* audioOut;
    QIODevice *buf;
    QUdpSocket *udpSocket;
};
