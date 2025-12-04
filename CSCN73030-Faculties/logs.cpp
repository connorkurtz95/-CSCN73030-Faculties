#include "logs.h"

Logs::Logs(int id)
{
    this->id = id;

    this->numOfReports = 0;

    this->repairFinished = 0;

    this->repairsUnfinished = 0;


    if (!loadFromDataBase())
    {
        //output failed to find database connected to id
    }
}

Logs::Logs(int id, Report init)
{
    this->id = id;

    this->numOfReports = 1;

    if(init.getRepairStatus())
    {
        this->repairFinished = 1;
        this->repairsUnfinished = 0;
    }
    else
    {
        this->repairFinished = 0;
        this->repairsUnfinished = 1;
    }

    this->reports = new Report[numOfReports];

    this->reports[this->numOfReports - 1] = init;
}

void Logs::addReport(Report& newRep)
{
    // allocate new array with one extra slot
    Report* temp = new Report[this->numOfReports + 1];

    // copy old elements if any
    for (int i = 0; i < this->numOfReports; ++i) {
        temp[i] = this->reports[i];  // invokes copy assignment
    }

    // add the new report at the end
    temp[this->numOfReports] = newRep;  // copy assignment

    // free old memory
    if (this->numOfReports > 0)
        delete[] this->reports;

    // update pointer and count
    this->reports = temp;
    this->numOfReports++;

    // update status flags
    if (newRep.getRepairStatus()) {
        this->repairFinished = 1;
        this->repairsUnfinished = 0;
    } else {
        this->repairFinished = 0;
        this->repairsUnfinished = 1;
    }
}

Logs::~Logs()
{
    if (!saveToDataBase())
    {
        //output and try again 3 times

        //if still failed output to a error text file?
    }

    if(numOfReports > 0)
    {
        delete[] this->reports;
    }
}


// private functions
bool Logs::loadFromDataBase()
{
    return true;
}

bool Logs::saveToDataBase()
{
    return true;
}
