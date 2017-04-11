#include "chatwindow.h"
#include "transceiver.h"
#include <string>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChatWindow w;
    Transceiver t;

    w.addChat("Group Chat");
    //w.writeMessage("Group Chat", "bar", "baz");

    w.show();

    QObject::connect(&t, &Transceiver::messageReceived,
            &w, [&w](quint8 source, QByteArray data) {
                w.writeMessage("Group Chat", QString::number(source), data);
            });
    QObject::connect(&w, &ChatWindow::newMessage,
            &t, [&t](QString chatname, QString message) {
                t.sendMessage(message.toUtf8());
            });

    //t.sendMessage("Hello world");
    return a.exec();
}
