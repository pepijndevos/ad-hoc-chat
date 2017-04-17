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
    w.setWindowSize(0.5);   // Set to 50% of the desktop size.

    Transceiver t;
    Router r(&t);
    ChatManager m(&r, &w);
    settings.setValue("dummy", "add your ip and interface here");

    // Set the default icon size
    QSize default_icon_size = QSize(350, 350);
    w.setChatIconSizes(default_icon_size);

    // Test: send PNG image
    // TODO: not all bytes sent?
    //    std::string image_path = "test_image.png";
    //    m.sendFile("Group Chat", image_path);

    w.show();
    return a.exec();
}
