#ifndef LOGS_H
#define LOGS_H

#include "report.h"


class Logs
{
    int id;

    int numOfReports;

    int repairFinished;

    int repairsUnfinished;

    Report* reports;


    bool loadFromDataBase();

    bool saveToDataBase();

public:
    Logs(int id);

    Logs(int id, Report init);

    void addReport(Report newRep);
    \
    ~Logs();
};

#endif // LOGS_H
