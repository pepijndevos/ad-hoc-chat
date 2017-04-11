#include "transceiver.h"

#include <iostream>

Transceiver::Transceiver(QObject *parent) : QObject(parent) {
    groupAddress = QHostAddress("228.0.0.1");

    udpSocket = new QUdpSocket(this);
    udpSocket->setSocketOption(QAbstractSocket::MulticastTtlOption, 255);
    //udpSocket->setSocketOption(QAbstractSocket::MulticastLoopbackOption, 1);
    udpSocket->bind(QHostAddress::AnyIPv4, 10000, QUdpSocket::ShareAddress);
    udpSocket->joinMulticastGroup(groupAddress);

    connect(udpSocket, &QUdpSocket::readyRead,
            this, &Transceiver::processPendingDatagrams);

}

void Transceiver::processPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        QHostAddress source;
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size(), &source);
        emit messageReceived(source.toIPv4Address() & 0xff, datagram);
    }
}

void Transceiver::sendMessage(QByteArray data) {
    udpSocket->writeDatagram(data.data(), data.size(),
                             groupAddress, 10000);
}
