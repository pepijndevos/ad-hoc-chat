#include <QtNetwork>
#include <QtMultimedia>
#include "router.h"
#include "Packet.pb.h"

class Voip : public QObject {
    Q_OBJECT

public:
    explicit Voip(QObject *parent = 0);

public slots:
    void processPendingMessage(pb::Packet*);

private slots:
    void handleStateChanged(QAudio::State);
    void processPendingAudio();

signals:
    void sendAudio(pb::Packet*);

private:
    QHostAddress groupAddress;
    QHostAddress my_ip;
    QAudioFormat format;
    QAudioInput* audioIn;
    QIODevice *inbuf;
    QMap<quint32, QIODevice*> outbuf;
};
