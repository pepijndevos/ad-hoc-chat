#include "transceiver.h"

#include <QTextStream>
#include <iostream>

Transceiver::Transceiver(QObject *parent) : QObject(parent) {
    /* Constructor */
    groupAddress = QHostAddress("228.0.0.1");

    udpSocket = new QUdpSocket(this);
    udpSocket->setSocketOption(QAbstractSocket::MulticastTtlOption, 255);
    //udpSocket->setSocketOption(QAbstractSocket::MulticastLoopbackOption, 1);
    udpSocket->bind(QHostAddress::AnyIPv4, 10000, QUdpSocket::ShareAddress);
    udpSocket->joinMulticastGroup(groupAddress);

    QTextStream qout(stdout);
    //qDebug() << udpSocket->multicastInterface().name();
    for (auto ifa : QNetworkInterface::allInterfaces()) {
        qout << ifa.name() << " " << ifa.index() << "\n";
    }
    int idx;
    qout << "Enter the interface nubmer to use: ";
    qout.flush();
    std::cin >> idx;
    udpSocket->setMulticastInterface(QNetworkInterface::interfaceFromIndex(idx));
    qout << "Using " << udpSocket->multicastInterface().name() << "\n";
    qout.flush();

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
    pkt.SerializeToArray(datagram.data(), size);
    udpSocket->writeDatagram(datagram.data(), datagram.size(),
                             groupAddress, 10000);
}
