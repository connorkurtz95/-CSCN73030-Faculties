#ifndef CALENDAR_H
#define CALENDAR_H

#include <QObject>
#include <QMap>
#include <QStringList>

class Calendar : public QObject
{
    Q_OBJECT

public:
    explicit Calendar(QObject *parent = nullptr);

    // Add an event to a specific day (1–31)
    void addEvent(int day, const QString &event);

    // Remove an event by exact match, returns true if removed
    bool removeEvent(int day, const QString &event);

    // Get all events for a specific day
    QStringList eventsForDay(int day) const;

    // Get all days that have events
    QList<int> daysWithEvents() const;

private:
    // Map of day → list of events
    QMap<int, QStringList> m_events;
};

#endif // CALENDAR_H
