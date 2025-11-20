#include "logsWindow.h"
#include "ui_logsWindow.h"
#include "ui_writeReportWindow.h"
#include "writeReportWindow.h"
#include <QDate>


LogsWindow::LogsWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LogsWindow), log(QDate::currentDate().year())
{   
    ui->setupUi(this);

    ui->ReportsTableWidget->setDragDropMode(QAbstractItemView::NoDragDrop);
    ui->ReportsTableWidget->setDragEnabled(false);
    ui->ReportsTableWidget->setAcceptDrops(false);

    ui->ReportsTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    for(int i = 0; i < log.getNumOfReports(); i++)
    {
        enterRow(i);
    }
}

LogsWindow::~LogsWindow()
{
    delete ui;
}


void LogsWindow::enterRow(int row)
{
    for(int i = 0; i < NUMDATATYPETABLE; i++)
    {
        enterCell(row, i);
    }

}
//enum dateTypes{ ID, SUBJECT, MACHINEID, STATUS, DATE };
void LogsWindow::enterCell(int row, int column)
{
    Report* buf = NULL;

    bool flag;
    QString result;


    buf = log.getReports();

    switch (column)
    {
    case ID:

        ui->ReportsTableWidget->item(row, column)->setText(QString::number(buf[row].getID()));

        break;


    case SUBJECT:

        ui->ReportsTableWidget->item(row, column)->setText(QString::fromStdString(buf[row].getSubject()));

        break;


    case MACHINEID:

        ui->ReportsTableWidget->item(row, column)->setText(QString::number(buf[row].getMachineID()));

        break;


    case STATUS:

        flag = buf[row].getRepairStatus();
        result = flag ? "true" : "false";

        ui->ReportsTableWidget->item(row, column)->setText(result);

        break;


    case DATE:

        break;


    default:
        break;
    }
}


void LogsWindow::addReport(string subject, string description, int machinID, int* partsID)
{
    Report buf(subject, description);

    buf.setMachineID(machinID);

    log.addReport(buf);
}


void LogsWindow::on_createReportBtn_clicked()
{
    WriteReportWindow *second = new WriteReportWindow(this);

    second->show();
    this->hide();
}


void LogsWindow::on_editReportBtn_clicked()
{

}


void LogsWindow::on_viewReportBtn_clicked()
{

}

