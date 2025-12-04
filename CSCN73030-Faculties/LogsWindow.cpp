#include "logsWindow.h"
#include "ui_logsWindow.h"
#include "writeReportWindow.h"
#include "calendarwidget.h"
#include <QDate>
#include <QPushButton>


LogsWindow::LogsWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LogsWindow), log(QDate::currentDate().year())
{   
    ui->setupUi(this);
    // Connect openCalendarBtn if it exists (safety in case UI naming differs)
    {
        QPushButton *btn = this->findChild<QPushButton *>("openCalendarBtn");
        if (btn) connect(btn, &QPushButton::clicked, this, &LogsWindow::on_openCalendarBtn_clicked);
    }


    ui->ReportsTableWidget->setDragDropMode(QAbstractItemView::NoDragDrop);
    ui->ReportsTableWidget->setDragEnabled(false);
    ui->ReportsTableWidget->setAcceptDrops(false);

    ui->ReportsTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    reloadReportsTable();
}

LogsWindow::~LogsWindow()
{
    delete ui;
}


void LogsWindow::fillRow(int row)
{
    for(int i = 0; i < NUMDATATYPETABLE; i++)
    {
        fillCell(row, i);
    }

}

void LogsWindow::fillCell(int row, int column)
{
    bool flag;
    QString result;
    QString buf;
    QTableWidgetItem *item;

    int Id = 0;
    string Subject;
    int MachineId = 0;

    switch (column)
    {
    case ID:
        Id = log.getReport(row).getID();

        buf = buf.number(Id);

        item = ui->ReportsTableWidget->item(row, column);
        if (!item)
        {
            item = new QTableWidgetItem();
            ui->ReportsTableWidget->setItem(row, column, item);
        }

        item->setText(buf);
        break;


    case SUBJECT:
        Subject = log.getReport(row).getSubject();

        buf = buf.fromStdString(Subject);

        item = ui->ReportsTableWidget->item(row, column);
        if (!item)
        {
            item = new QTableWidgetItem();
            ui->ReportsTableWidget->setItem(row, column, item);
        }

        item->setText(buf);
        break;


    case MACHINEID:
        MachineId = log.getReport(row).getMachineID();

        buf = buf.number(MachineId);

        item = ui->ReportsTableWidget->item(row, column);
        if (!item)
        {
            item = new QTableWidgetItem();
            ui->ReportsTableWidget->setItem(row, column, item);
        }

        item->setText(buf);
        break;


    case STATUS:
        flag = log.getReport(row).getRepairStatus();
        result = flag ? "In Progress" : "Completed";

        item = ui->ReportsTableWidget->item(row, column);
        if (!item)
        {
            item = new QTableWidgetItem();
            ui->ReportsTableWidget->setItem(row, column, item);
        }

        item->setText(result);
        break;


    case DATE:

        break;


    default:
        break;
    }
}


void LogsWindow::addReport(string subject, string description, int machinID)
{
    Report buf(log.getNumOfReports(), subject, description, machinID);

    log.addReport(buf);
}

void  LogsWindow::addTableRow()
{
    int newRow = ui->ReportsTableWidget->rowCount();

    ui->ReportsTableWidget->insertRow(newRow);
}

bool LogsWindow::checkForReports()
{
    return numDisplayedReports < log.getNumOfReports();
}

void LogsWindow::reloadReportsTable()
{
    int reportCount = log.getNumOfReports();
    int currentRows = ui->ReportsTableWidget->rowCount();

    while (currentRows < reportCount)
    {
        addTableRow();
        currentRows++;
    }

    while (currentRows > reportCount)
    {
        ui->ReportsTableWidget->removeRow(currentRows - 1);
        currentRows--;
    }

    for (int i = 0; i < reportCount; i++)
    {
        fillRow(i);
    }

    numDisplayedReports = reportCount;
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


void LogsWindow::on_reloadReportsBtn_clicked()
{
    reloadReportsTable();
}



void LogsWindow::on_openCalendarBtn_clicked()
{
    // Create calendar as a top-level window (no parent) so it remains after closing LogsWindow
    CalendarWidget *cw = new CalendarWidget(nullptr);
    cw->setAttribute(Qt::WA_DeleteOnClose);
    cw->show();

    // Close the logs window
    this->close();
}
