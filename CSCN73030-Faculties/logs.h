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


    bool loadFromDataBase(); // not setup

    bool saveToDataBase(); // not setup

public:
    //(de)constructors
    Logs(int id);

    Logs(int id, Report init);

    void addReport(Report& newRep);

    ~Logs();

    // Getters
    int getId() const { return id; }

    int getNumOfReports() const { return numOfReports; }

    int getRepairFinished() const { return repairFinished; }

    int getRepairsUnfinished() const { return repairsUnfinished; }

    Report* getReports() { return reports; }


    Report getReport(int reportNum) { return reports[reportNum]; }

};

#endif // LOGS_H
