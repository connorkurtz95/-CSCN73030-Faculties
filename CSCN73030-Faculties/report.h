#ifndef REPORT_H
#define REPORT_H

#include <string>


#define MAXNUMOFLINKS 10

using namespace std;


enum dateTypes{ ID, SUBJECT, MACHINEID, STATUS, DATE };


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


    ~Report();


    void addPart(int partIDs);


    void setSubject(string subject) { this->subject = subject; }

    void setDescription(string decription) { this->description = decription; }

    void setRepairStatus(bool repairStatus)
    {
        this->repairStatus = repairStatus;

        //this->finished.set(finished.current());
    }

    void setMachineID(int machineID) { this->machineID = machineID; }


    int getID(void) { return id; }

    string getSubject(void) { return subject; }

    string getDescription(void) { return description; }

    bool getRepairStatus(void) { return repairStatus; }

    int getMachineID(void) { return machineID; }

    int getPartsId(int partListPosition) { return partIDs[partListPosition]; }
};


//typedef report* Report;

#endif // REPORT_H
