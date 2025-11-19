#include "Calendar.h"

Calendar::Calendar(QObject *parent)
    : QObject(parent)
{
}

void Calendar::addEvent(int day, const QString &event)
{
    if (day < 1 || day > 31)
        return;

    m_events[day].append(event);
}

bool Calendar::removeEvent(int day, const QString &event)
{
    if (!m_events.contains(day))
        return false;

    bool removed = m_events[day].removeOne(event);

    // If the list becomes empty, remove the key entirely
    if (m_events[day].isEmpty())
        m_events.remove(day);

    return removed;
}

QStringList Calendar::eventsForDay(int day) const
{
    return m_events.value(day);
}

QList<int> Calendar::daysWithEvents() const
{
    return m_events.keys();
}
