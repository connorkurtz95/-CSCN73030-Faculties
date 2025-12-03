#ifndef CALENDARWIDGET_H
#define CALENDARWIDGET_H

#include <QWidget>
#include <QCalendarWidget>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "Calendar.h"

class CalendarWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CalendarWidget(QWidget *parent = nullptr);

private slots:
    void onDateSelected(const QDate &date);
    void onAddEvent();
    void onRemoveEvent();

private:
    Calendar m_calendar;

    QCalendarWidget *m_qtCalendar;
    QListWidget *m_eventList;
    QLineEdit *m_eventInput;
    QPushButton *m_addButton;
    QPushButton *m_removeButton;

    void refreshEventList(const QDate &date);
};

#endif // CALENDARWIDGET_H
