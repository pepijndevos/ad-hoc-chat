#include "voip.h"

Voip::Voip(QObject *parent) : QObject(parent) {
    groupAddress = QHostAddress("228.0.0.1");

    QAudioFormat format;
    // Set up the desired format, for example:
    format.setSampleRate(8000);
    format.setChannelCount(1);
    format.setSampleSize(8);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::UnSignedInt);

    QAudioDeviceInfo info = QAudioDeviceInfo::defaultInputDevice();
    qDebug() << info.supportedCodecs();
    if (!info.isFormatSupported(format)) {
        qWarning() << "Default format not supported, trying to use the nearest.";
        format = info.nearestFormat(format);
    }

    audioIn = new QAudioInput(format, this);
    connect(audioIn, &QAudioInput::stateChanged, this, &Voip::handleStateChanged);
    qDebug() << audioIn->periodSize() << audioIn->bufferSize();

    audioOut = new QAudioOutput(format, this);
    connect(audioOut, &QAudioOutput::stateChanged, this, &Voip::handleStateChanged);
    audioOut->setBufferSize(8000);
    qDebug() << audioOut->periodSize() << audioOut->bufferSize();

    udpSocket = new QUdpSocket(this);
    udpSocket->setSocketOption(QAbstractSocket::MulticastTtlOption, 255);
    udpSocket->setSocketOption(QAbstractSocket::MulticastLoopbackOption, 0);
    udpSocket->bind(QHostAddress::AnyIPv4, 10001, QUdpSocket::ShareAddress);
    udpSocket->joinMulticastGroup(groupAddress);

    connect(udpSocket, &QUdpSocket::readyRead,
            this, &Voip::processPendingDatagrams);
}

void Voip::processPendingDatagrams() {
    /* Handle packet reception */
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        QHostAddress source;
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size(), &source);

        buf->write(datagram);
    }
}

void Voip::call(quint32 ip) {
    QHostAddress addr(ip);
    udpSocket->connectToHost(addr, 10001);
    audioIn->start(udpSocket);
    buf = audioOut->start();
}

void Voip::handleStateChanged(QAudio::State state) {
    qDebug() << state;
}
