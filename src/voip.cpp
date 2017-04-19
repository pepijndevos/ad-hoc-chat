#include "voip.h"

Voip::Voip(QObject *parent) : QObject(parent) {
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

    inbuf = audioIn->start();
    connect(inbuf, &QIODevice::readyRead,
            this, &Voip::processPendingAudio);

}

void Voip::processPendingAudio() {
    QByteArray data = inbuf->readAll();
    pb::Packet p;
    p.set_audio(data.data(), data.size());
    p.set_message_type(pb::Packet::VOIP);
    emit sendAudio(&p);
}

void Voip::processPendingMessage(pb::Packet *pkt) {
    pb::Packet p = *pkt;
    if(p.message_type() == pb::Packet::VOIP) {
        quint32 ip = p.sender_ip();
        QIODevice *buf;
        if(!outbuf.contains(ip)) {
            QAudioOutput *audio = new QAudioOutput(format, this);
            connect(audio, &QAudioOutput::stateChanged, this, &Voip::handleStateChanged);
            audio->setBufferSize(8000);
            buf = audio->start();
            outbuf.insert(ip, buf);
        } else {
            buf = outbuf.value(ip);
        }
        std::string data = p.audio();
        buf->write(data.data(), data.size());
    }
}

void Voip::handleStateChanged(QAudio::State state) {
    qDebug() << state;
}
