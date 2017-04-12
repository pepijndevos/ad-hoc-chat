#include "chatwindow.h"
#include "transceiver.h"
#include "router.h"
#include "Packet.pb.h"
#include "Message.pb.h"
#include <string>
#include <QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("UTwente");
    QCoreApplication::setOrganizationDomain("utwente.nl");
    QCoreApplication::setApplicationName("Chat");

    QApplication a(argc, argv);
    QSettings settings;

    ChatWindow w;
    Transceiver t;
    Router r(&t);

    settings.setValue("dummy", "add your ip and interface here");

    w.addChat("Group Chat");
    //w.writeMessage("Group Chat", "bar", "baz");

    w.show();

    QObject::connect(&r, &Router::messageReceived,
            &w, [&w](pb::Packet p) {
                pb::Message msg = p.msg();
                w.writeMessage("Group Chat",
                        QString::fromStdString(msg.name()),
                        QString::fromStdString(msg.text()));
            });
    QObject::connect(&w, &ChatWindow::newMessage,
            &r, [&r](QString chatname, QString message) {
                QSettings settings;
                pb::Packet p;
                pb::Message *msg = p.mutable_msg();
                QString name = settings.value("name", "Me").toString();
                QString ip = settings.value("ip", "192.168.1.255").toString();
                msg->set_name(name.toStdString());
                msg->set_text(message.toStdString());
                p.set_message_type(pb::Packet::MESSAGE);
                p.set_sender_ip(QHostAddress(ip).toIPv4Address());
                p.add_receiver_ip(QHostAddress("192.168.5.1").toIPv4Address());
                p.add_receiver_ip(QHostAddress("192.168.5.2").toIPv4Address());
                p.add_receiver_ip(QHostAddress("192.168.5.3").toIPv4Address());
                p.add_receiver_ip(QHostAddress("192.168.5.4").toIPv4Address());
                r.sendMessage(p);
            });

    //t.sendMessage("Hello world");
    return a.exec();
}
