#include "Part.h"

/*!
 * \brief Base constructor for the Part class
 */
Part::Part()
{
    partType = "";
    aquisitionDate = "";
    partID = 0;
    partDescription = "";
    partState = 0;
}

/*!
 * \brief Part::Part parameterized contstuctor implementation for the Part class
 * \param partType
 * \param aquisitionDate
 * \param partID
 * \param partDescription
 */
Part::Part(std::string partType, std::string aquisitionDate, int partID, std::string partDescription, bool partState){
    this->aquisitionDate = aquisitionDate;
    this->partType = partType;
    this->partID = partID;
    this->partDescription = partDescription;
    this->partState = partState;
}

