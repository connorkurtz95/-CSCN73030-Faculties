#include "report.h"

Report::Report()
{
    this->numOfParts = 0;

    this->id = 0;
}

Report::Report(int id, string subject, string decription, int *partIDs, int numOfParts, int machineId)
{
    this->id = id;

    this->subject = subject;

    this->description = decription;

    this->numOfParts = numOfParts;

    this->partIDs = new int[numOfParts];

    this->machineID = machineId;

    memcpy(this->partIDs, partIDs, numOfParts);
}

Report::Report(int id, string subject, string decription, int machineId)
{
    this->numOfParts = 0;

    this->subject = subject;

    this->id = id;

    this->machineID = machineId;

    this->description = decription;
}

Report::Report(string subject, string decription, int *partIDs, int numOfParts, int machineId)
{
    this->numOfParts = 0;

    this->id = 0;

    this->subject = subject;

    this->description = decription;

    this->numOfParts = numOfParts;

    this->partIDs = new int(numOfParts);

    this->machineID = machineId;

    memcpy(this->partIDs, partIDs, numOfParts);
}

Report::Report(string subject, string decription, int machineId)
{
    this->numOfParts = 0;

    this->id = 0;

    this->subject = subject;

    this->machineID = machineId;

    this->description = decription;
}

Report::Report(const Report& other)
    : id(other.id),
    subject(other.subject),
    description(other.description),
    repairStatus(other.repairStatus),
    machineID(other.machineID),
    numOfParts(other.numOfParts),
    partIDs(nullptr)
{
    if (numOfParts > 0 && other.partIDs != nullptr)
    {
        partIDs = new int[numOfParts];
        for (int i = 0; i < numOfParts; ++i)
        {
            partIDs[i] = other.partIDs[i];
        }
    }
}




Report& Report::operator=(Report& other)
{
    if (this != &other)
    {
        // Free existing resources
        if (this->numOfParts > 0)
            delete[] partIDs;

        // Transfer ownership
        id = other.id;

        subject = std::move(other.subject);
        description = std::move(other.description);

        repairStatus = other.repairStatus;

        machineID = other.machineID;

        numOfParts = other.numOfParts;
        partIDs = other.partIDs;
    }

    return *this;
}



Report::~Report()
{
    if(numOfParts > 0)
    {
        delete[] partIDs;
    }
}


void Report::addPart(int partID)
{
    // allocate new array with one extra slot
    int* temp = new int[this->numOfParts + 1];

    // copy old elements if any
    if (this->numOfParts > 0) {
        memcpy(temp, this->partIDs, this->numOfParts * sizeof(int));
    }

    // add the new part at the end
    temp[this->numOfParts] = partID;

    // free old memory
    delete[] this->partIDs;

    // update pointer and count
    this->partIDs = temp;
    this->numOfParts++;
}

