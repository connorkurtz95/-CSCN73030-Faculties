#include "logsWindow.h"
#include "ui_logsWindow.h"

LogsWindow::LogsWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LogsWindow)
{
    ui->setupUi(this);
}

LogsWindow::~LogsWindow()
{
    delete ui;
}
