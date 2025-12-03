#include "calendarwidget.h"

CalendarWidget::CalendarWidget(QWidget *parent)
    : QWidget(parent)
{
    // --- Widgets ---
    m_qtCalendar = new QCalendarWidget(this);
    m_eventList  = new QListWidget(this);
    m_eventInput = new QLineEdit(this);
    m_addButton  = new QPushButton("Add Event", this);
    m_removeButton = new QPushButton("Remove Selected Event", this);

    // --- Layout ---
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_qtCalendar);

    auto *eventLayout = new QVBoxLayout();
    eventLayout->addWidget(m_eventList);
    eventLayout->addWidget(m_eventInput);

    auto *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(m_addButton);
    buttonLayout->addWidget(m_removeButton);

    eventLayout->addLayout(buttonLayout);
    mainLayout->addLayout(eventLayout);

    setLayout(mainLayout);

    // --- Connections ---
    connect(m_qtCalendar, &QCalendarWidget::clicked,
            this, &CalendarWidget::onDateSelected);

    connect(m_addButton, &QPushButton::clicked,
            this, &CalendarWidget::onAddEvent);

    connect(m_removeButton, &QPushButton::clicked,
            this, &CalendarWidget::onRemoveEvent);

    // Load today’s events when the widget loads
    onDateSelected(QDate::currentDate());
}

void CalendarWidget::onDateSelected(const QDate &date)
{
    refreshEventList(date);
}

void CalendarWidget::refreshEventList(const QDate &date)
{
    m_eventList->clear();

    int day = date.day();

    QStringList events = m_calendar.eventsForDay(day);
    m_eventList->addItems(events);
}

void CalendarWidget::onAddEvent()
{
    QDate date = m_qtCalendar->selectedDate();
    int day = date.day();
    QString text = m_eventInput->text().trimmed();

    if (text.isEmpty())
        return;

    m_calendar.addEvent(day, text);
    m_eventInput->clear();
    refreshEventList(date);
}

void CalendarWidget::onRemoveEvent()
{
    QDate date = m_qtCalendar->selectedDate();
    int day = date.day();

    QListWidgetItem *selected = m_eventList->currentItem();
    if (!selected)
        return;

    QString eventText = selected->text();

    m_calendar.removeEvent(day, eventText);
    refreshEventList(date);
}
