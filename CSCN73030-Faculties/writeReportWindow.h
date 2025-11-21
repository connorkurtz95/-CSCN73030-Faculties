#ifndef WRITEREPORTWINDOW_H
#define WRITEREPORTWINDOW_H

#include "logsWindow.h"
#include <QMainWindow>

namespace Ui {
class WriteReportWindow;
}

class WriteReportWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit WriteReportWindow(QWidget *parent = nullptr);
    ~WriteReportWindow();

private slots:
    void on_closeBtn_clicked();

    void on_saveBtn_clicked(); // not done

private:
    Ui::WriteReportWindow *ui;
};

#endif // WRITEREPORTWINDOW_H
