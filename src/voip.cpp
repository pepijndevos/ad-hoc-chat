#include "voip.h"

Voip::Voip(QObject *parent) : QObject(parent) {
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

    //connect(router, &Router::messageReceived,
    //        this, &Voip::processPendingMessage);

    inbuf = audioIn->start();
    connect(inbuf, &QIODevice::readyRead,
            this, &Voip::processPendingAudio);

    outbuf = audioOut->start();
}

void Voip::processPendingAudio() {
    QByteArray data = inbuf->readAll();
    pb::Packet p;
    p.set_audio(data.data(), data.size());
    p.set_message_type(pb::Packet::VOIP);
    emit sendAudio(p);
}

void Voip::processPendingMessage(pb::Packet p) {
    if(p.message_type() == pb::Packet::VOIP) {
        std::string data = p.audio();
        outbuf->write(data.data(), data.size());
    }
}

void Voip::handleStateChanged(QAudio::State state) {
    qDebug() << state;
}
