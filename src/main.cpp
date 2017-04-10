#include "chatwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChatWindow w;

    w.addChat("foo");
    w.writeMessage("foo", "bar", "baz");

    w.show();

    return a.exec();
}
