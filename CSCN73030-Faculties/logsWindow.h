#ifndef LOGSWINDOW_H
#define LOGSWINDOW_H

#include "logs.h"
#include <QtWidgets/QMainWindow>


#define NUMDATATYPETABLE 5


namespace Ui {
class LogsWindow;
}

class LogsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LogsWindow(QWidget *parent = nullptr);
    ~LogsWindow();

    void addReport(string subject, string description, int machinID, int* partsID); // not done

    void addTableRow();

private slots:
    void on_createReportBtn_clicked();

    void on_editReportBtn_clicked();

    void on_viewReportBtn_clicked();

private:
    Ui::LogsWindow *ui;

    Logs log;


    void enterRow(int row);
    void enterCell(int row, int column);
};

#endif // LOGSWINDOW_H
