#include "transceiver.h"

#include <iostream>

Transceiver::Transceiver(QObject *parent) : QObject(parent) {
    groupAddress = QHostAddress("228.0.0.1");

    udpSocket = new QUdpSocket(this);
    udpSocket->setSocketOption(QAbstractSocket::MulticastTtlOption, 255);
    //udpSocket->setSocketOption(QAbstractSocket::MulticastLoopbackOption, 1);
    udpSocket->bind(QHostAddress::AnyIPv4, 10000, QUdpSocket::ShareAddress);
    udpSocket->joinMulticastGroup(groupAddress);

    qDebug() << udpSocket->multicastInterface().name();
    for (auto ifa : QNetworkInterface::allInterfaces()) {
        qDebug() << ifa.name();
    }
    //udpSocket->setMulticastInterface(QNetworkInterface::interfaceFromName("wlan0"));
    //qDebug() << udpSocket->multicastInterface().name();

    connect(udpSocket, &QUdpSocket::readyRead,
            this, &Transceiver::processPendingDatagrams);

}

void Transceiver::processPendingDatagrams() {
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        QHostAddress source;
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size(), &source);
        qDebug() << "Packet received" << source.toString();

        // TODO: for now, it only gets the payload string
        MessageProto::Message msg = parseRecvd(datagram);

        emit messageReceived(source.toIPv4Address() & 0xff, msg.payload().c_str());
    }
}

MessageProto::Message Transceiver::parseRecvd(QByteArray datagram_data){
    /* Deserializes the received protobuf */
    MessageProto::Message msg;
    msg.ParseFromArray(datagram_data, datagram_data.size());
    return msg;
}

void Transceiver::sendMessage(QByteArray data) {
    udpSocket->writeDatagram(data.data(), data.size(),
                             groupAddress, 10000);
}

void Transceiver::sendString(std::string data){
    // TODO: Create actual packet instead of a dummy one.
    Packet pkt(data, 0, 0, 0, "1", true, false, false, false);

    QByteArray d = router.forward(&pkt);
    if(d.length() == 0){
        return;
    }

    sendMessage(d);
}
