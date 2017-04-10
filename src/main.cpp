#include "chatwindow.h"
#include "adhoc.h"
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

    QApplication a(argc, argv);
    ChatWindow w;
    w.show();

    // Initialize the Ad-hoc network
    adhoc_setup(INTERFACE, GROUP, COMPUTER_ID);

    int ret_val = a.exec();

    // Destroy the Ad-hoc network
    adhoc_desetup(INTERFACE, GROUP);

    delete exec_name;
    return ret_val;
}
