#include "writeReportWindow.h"
#include "logsWindow.h"
#include "ui_writeReportWindow.h"


WriteReportWindow::WriteReportWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::WriteReportWindow)
{
    ui->setupUi(this);
}

WriteReportWindow::~WriteReportWindow()
{
    delete ui;
}

void WriteReportWindow::on_closeBtn_clicked()
{
    parentWidget()->show();  // show the parent (MainWindow)
    this->close();
}


void WriteReportWindow::on_saveBtn_clicked()
{
    LogsWindow *parent = qobject_cast<LogsWindow*>(this->parentWidget());
    if (parent) {

        string subject = ui->subjectTextEdit->toPlainText().toStdString();

        string description = ui->descriptionTextEdit->toPlainText().toStdString();

        int machineID = ui->machineIDTextEdit->toPlainText().toInt();

        parent->addReport(subject, description, machineID);
        parent->reloadReportsTable();
    }



    on_closeBtn_clicked();
}

