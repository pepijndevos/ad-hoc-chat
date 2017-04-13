#include "chatwindow.h"
#include "transceiver.h"
#include "router.h"
#include "chatmanager.h"
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
    ChatManager m(&r, &w);
    settings.setValue("dummy", "add your ip and interface here");

    w.show();
    return a.exec();
}
