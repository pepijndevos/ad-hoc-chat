#include "chatwindow.h"
#include "transceiver.h"
#include <string>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChatWindow w;
    Transceiver t;

    w.addChat("foo");
    w.writeMessage("foo", "bar", "baz");

    w.show();

    t.sendMessage("Hello world");

    return a.exec();
}
