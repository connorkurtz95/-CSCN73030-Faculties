#include <QCoreApplication>
#include <Qapplication.h>
#include "logsWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LogsWindow w;
    w.show();
    return a.exec();
}
