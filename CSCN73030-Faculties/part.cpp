#include "Part.h"

Part::Part()
{
    partType = "";
    aquisitionDate = "";
    partID = 0;
    partDescription = "";
}

Part::Part(std::string partType, std::string aquisitionDate, int partID, std::string partDescription){
    this->aquisitionDate = aquisitionDate;
    this->partType = partType;
    this->partID = partID;
    this->partDescription = partDescription;
}

