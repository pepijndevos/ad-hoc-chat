#include "transceiver.h"

#include <iostream>

Transceiver::Transceiver(QObject *parent) : QObject(parent) {
    sequence_number = 0;
    groupAddress = QHostAddress("228.0.0.1");

    udpSocket = new QUdpSocket(this);
    udpSocket->setSocketOption(QAbstractSocket::MulticastTtlOption, 255);
    //udpSocket->setSocketOption(QAbstractSocket::MulticastLoopbackOption, 1);
    udpSocket->bind(QHostAddress::AnyIPv4, 10000, QUdpSocket::ShareAddress);
    udpSocket->joinMulticastGroup(groupAddress);

    //qDebug() << udpSocket->multicastInterface().name();
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

        pb::Packet pkt;
        pkt.ParseFromArray(datagram.data(), datagram.size());

        emit messageReceived(pkt);
    }
}

void Transceiver::sendMessage(pb::Packet pkt) {
    QByteArray datagram;
    int size = pkt.ByteSizeLong();
    datagram.resize(size);
    pkt.set_sequence_number(sequence_number++);
    pkt.SerializeToArray(datagram.data(), size);
    udpSocket->writeDatagram(datagram.data(), datagram.size(),
                             groupAddress, 10000);
}
