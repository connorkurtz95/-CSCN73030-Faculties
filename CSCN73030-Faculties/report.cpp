#include <iostream>
#include "report.h"


Report::Report()
{

}

Report::Report(int id, string name, string decription, int *partIDs, const int numOfParts)
{
    this->id = id;

    this->name = name;

    this->decription = decription;

    this->partIDs = new int(numOfParts);

    memcpy(this->partIDs, partIDs, numOfParts);
}

Report::Report(int id, string name, string decription)
{
    this->id = id;

    this->name = name;

    this->decription = decription;
}

Report::Report(string name, string decription, int *partIDs, const int numOfParts)
{
    this->name = name;

    this->decription = decription;

    this->partIDs = new int(numOfParts);

    memcpy(this->partIDs, partIDs, numOfParts);
}

Report::Report(string name, string decription)
{
    this->name = name;

    this->decription = decription;
}
