#include "chatwindow.h"
#include "utils.h"
#include <string>
#include <QApplication>

/* Settings for the Ad-hoc network */
#define INTERFACE "wlan0"
#define GROUP "1"
#define COMPUTER_ID "1"

int main(int argc, char *argv[])
{
    setExecName(argv[0]);
    setComputerId(COMPUTER_ID);

    QApplication a(argc, argv);
    ChatWindow w;
    w.show();

    int ret_val = a.exec();

    delete exec_name;
    delete computer_id;

    return ret_val;
}
