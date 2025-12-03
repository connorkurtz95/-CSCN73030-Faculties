#include <QCoreApplication>
#include <Qapplication.h>
#include "CalendarWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CalendarWidget w;
    w.show();
    return a.exec();
}
