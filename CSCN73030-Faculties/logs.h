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

public:
    Logs();

    Logs(Report init);

    void addReport(Report newRep);
};

#endif // LOGS_H
