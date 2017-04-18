#include "chatwindow.h"
#include "transceiver.h"
#include "router.h"
#include "chatmanager.h"
#include "voip.h"
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
    w.setWindowSize(0.5);   // Set to 50% of the desktop size.

    Transceiver t;
    Router r(&t);
    ChatManager m(&r, &w);
    settings.setValue("dummy", "add your ip and interface here");

    Voip v;
    //v.call(QHostAddress("127.0.0.1").toIPv4Address());

    // Set the default icon size
    QSize default_icon_size = QSize(350, 350);
    w.setChatIconSizes(default_icon_size);

    w.show();
    return a.exec();
}
