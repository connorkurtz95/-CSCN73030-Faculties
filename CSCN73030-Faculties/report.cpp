#include <iostream>
#include "report.h"

Report::Report()
{
    this->numOfParts = 0;
}


Report::Report(int id, string subject, string decription, int *partIDs, int numOfParts)
{
    this->id = id;

    this->subject = subject;

    this->description = decription;

    this->numOfParts = numOfParts;

    this->partIDs = new int[numOfParts];

    memcpy(this->partIDs, partIDs, numOfParts);
}

Report::Report(int id, string subject, string decription)
{
    this->subject = subject;

    this->id = id;

    this->description = decription;
}

Report::Report(string subject, string decription, int *partIDs, int numOfParts)
{
    this->subject = subject;

    this->description = decription;

    this->numOfParts = numOfParts;

    this->partIDs = new int(numOfParts);

    memcpy(this->partIDs, partIDs, numOfParts);
}

Report::Report(string subject, string decription)
{
    this->subject = subject;

    this->description = decription;
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

