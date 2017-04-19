#include "chatwindow.h"
#include "transceiver.h"
#include "router.h"
#include "chatmanager.h"
#include "Raft.h"
#include "Packet.pb.h"
#include "Message.pb.h"

#include <string>
#include <QApplication>
#include <QHostAddress>

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("UTwente");
    QCoreApplication::setOrganizationDomain("utwente.nl");
    QCoreApplication::setApplicationName("Chat");

    QApplication a(argc, argv);
    QSettings settings;

    ChatWindow w;
    w.setWindowSize(0.5);   // Set to 50% of the desktop size.

    Transceiver t;
    Router r(&t);
    Raft raft;

    uint32_t my_ip = QHostAddress(settings.value("ip").toString()).toIPv4Address();
    raft.setMyIp(my_ip);
    raft.setRouter(&r);

    ChatManager m(&r, &w, &raft);
    settings.setValue("dummy", "add your ip and interface here");

    // Set the default icon size
    QSize default_icon_size = QSize(350, 350);
    w.setChatIconSizes(default_icon_size);

    w.show();
    return a.exec();
}
