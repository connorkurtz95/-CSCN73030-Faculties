#ifndef REPORT_H
#define REPORT_H

#include <string>
#include "logs.h"

#define MAXNUMOFLINKS 10

using namespace std;


class Report : public Logs
{
    int id;

    string name;

    string subjuect;

    string decription;

    bool repairStatus;

    int machineID;

    int *partIDs;

public:
    Report();

    Report(int id, string name, string decription, int *partIDs, const int numOfParts);

    Report(int id, string name, string decription);

    Report(string name, string decription, int *partIDs, const int numOfParts);

    Report(string name, string decription);
};

#endif // REPORT_H
