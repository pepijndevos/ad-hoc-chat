#include "voip.h"

Voip::Voip(QObject *parent) : QObject(parent) {
    groupAddress = QHostAddress("228.0.0.1");
    //groupAddress = QHostAddress("127.0.0.1");

    QSettings settings;
    my_ip = QHostAddress(settings.value("ip").toString());

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

    QString name = settings.value("interface").toString();
    udpSocket->setMulticastInterface(QNetworkInterface::interfaceFromName(name));

    connect(udpSocket, &QUdpSocket::readyRead,
            this, &Voip::processPendingDatagrams);

    inbuf = audioIn->start();
    connect(inbuf, &QIODevice::readyRead,
            this, &Voip::processPendingAudio);

    outbuf = audioOut->start();
}

void Voip::processPendingAudio() {
    QByteArray datagram = inbuf->readAll();
    udpSocket->writeDatagram(datagram.data(), datagram.size(),
                             groupAddress, 10001);
}

void Voip::processPendingDatagrams() {
    /* Handle packet reception */
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        QHostAddress source;
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size(), &source);

        if (source == my_ip) return;
        //qDebug() << source;

        outbuf->write(datagram);
    }
}

void Voip::handleStateChanged(QAudio::State state) {
    qDebug() << state;
}
