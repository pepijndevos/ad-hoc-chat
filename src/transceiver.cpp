#include "transceiver.h"

Transceiver::Transceiver(QObject *parent) : QObject(parent) {
    /* Constructor */
    groupAddress = QHostAddress("228.0.0.1");

    udpSocket = new QUdpSocket(this);
    udpSocket->setSocketOption(QAbstractSocket::MulticastTtlOption, 255);
    udpSocket->setSocketOption(QAbstractSocket::MulticastLoopbackOption, 0);
    udpSocket->bind(QHostAddress::AnyIPv4, 10000, QUdpSocket::ShareAddress);
    udpSocket->joinMulticastGroup(groupAddress);

    QSettings settings;
    QString name = settings.value("interface").toString();
    udpSocket->setMulticastInterface(QNetworkInterface::interfaceFromName(name));
    //qDebug() << udpSocket->multicastInterface().name();

    connect(udpSocket, &QUdpSocket::readyRead,
            this, &Transceiver::processPendingDatagrams);

}

void Transceiver::processPendingDatagrams() {
    /* Handle packet reception */
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        QHostAddress source;
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size(), &source);

        CFB_Mode<AES>::Decryption cfbDecryption((byte*)key, sizeof(key), (byte*)iv);
        cfbDecryption.ProcessData((byte*)datagram.data(), (byte*)datagram.data(), datagram.size());

        pb::Packet pkt;
        pkt.ParseFromArray(datagram.data(), datagram.size());

        //qDebug() << "Packet received" << source.toString() << pkt.DebugString().c_str();

        emit messageReceived(pkt);
    }
}

bool Transceiver::sendMessage(pb::Packet pkt) {
    QByteArray datagram;
    int size = pkt.ByteSize();
    datagram.resize(size);
    pkt.SerializeToArray(datagram.data(), size);

    CFB_Mode<AES>::Encryption cfbEncryption((byte*)key, sizeof(key), (byte*)iv);
    cfbEncryption.ProcessData((byte*)datagram.data(), (byte*)datagram.data(), datagram.size());

    int written = udpSocket->writeDatagram(datagram.data(), datagram.size(), groupAddress, 10000);

    return written == datagram.size();
}
