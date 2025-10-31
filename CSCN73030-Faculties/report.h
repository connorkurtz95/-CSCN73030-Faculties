#ifndef REPORT_H
#define REPORT_H

#include <string>


#define MAXNUMOFLINKS 10

using namespace std;


class Report
{
    int id;

    string subject;

    string description;

    //Date started;

    //Date finished;

    bool repairStatus;

    int machineID;

    int numOfParts;

    int* partIDs;

public:
    Report();

    Report(int id, string subject, string decription, int *partIDs, const int numOfParts);

    Report(int id, string subject, string decription);

    Report(string subject, string decription, int *partIDs, const int numOfParts);

    Report(string subject, string decription);


    void setSubject(string subject);

    void setDescription(string decription);

    void setRepairStatus(bool repairStatus);

    void setMachineID(int machineID);

    void setPartsList(int partIDs);


    string getSubject(void);

    string getDescription(void);

    bool getRepairStatus(void);

    int getMachineID(void);

    int getPartsId(int partListPosition);
};

#endif // REPORT_H
