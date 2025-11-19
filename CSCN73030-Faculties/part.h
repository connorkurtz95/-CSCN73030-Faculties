#ifndef PART_H
#define PART_H

#include <string>

/*!
 * \brief The Part class
 * \details Represents a component or part in the project database.
 * Stores details such as part type, acquisition date, unique identifier,
 * description, and current operational state.
 */
class Part
{

private:
    std::string partType;          //!< The type or category of the part.
    std::string aquisitionDate;    //!< The date when the part was acquired.
    int partID;                    //!< Unique identifier for the part.
    std::string partDescription;   //!< A short textual description of the part.
    bool partState;                //!< Current state of the part (true = working, false = broken).

public:
    /*!
     * \brief Default constructor for the Part class.
     * \details Initializes all member variables to default values.
     */
    Part();

    /*!
     * \brief Parameterized constructor for the Part class.
     * \param partType The type or category of the part.
     * \param aquisitionDate The date when the part was acquired.
     * \param partID The unique identifier for the part.
     * \param partDescription A textual description of the part.
     */
    Part(std::string partType, std::string aquisitionDate, int partID, std::string partDescription, bool partState);

    /*!
     * \brief Gets the type of the part.
     * \return The part type as a string.
     */
    std::string GetPartType(){
        return this->partType;
    }

    /*!
     * \brief Sets the type of the part.
     * \param partType The new part type to assign.
     */
    void SetPartType(std::string partType){
        this->partType = partType;
    }

    /*!
     * \brief Gets the acquisition date of the part.
     * \return The acquisition date as a string.
     */
    std::string GetAquisitionDate(){
        return this->aquisitionDate;
    }

    /*!
     * \brief Sets the acquisition date of the part.
     * \param partType The new acquisition date to assign.
     * \note The parameter name should ideally be updated to reflect acquisition date.
     */
    void SetAquisitionDate(std::string partType){
        this->partType = partType;
    }

    /*!
     * \brief Gets the unique identifier of the part.
     * \return The part ID as an integer.
     */
    int GetPartID(){
        return this->partID;
    }

    /*!
     * \brief Sets the unique identifier for the part.
     * \param partID The new part ID to assign.
     */
    void SetPartID(int partID){
        this->partID = partID;
    }

    /*!
     * \brief Gets the description of the part.
     * \return The part description as a string.
     */
    std::string GetPartDesc(){
        return this->partDescription;
    }

    /*!
     * \brief Sets the description for the part.
     * \param partDesc The new description to assign.
     */
    void SetPartDesc(std::string partDesc){
        this->partDescription = partDesc;
    }

    /*!
     * \brief Gets the operational state of the part.
     * \return True if the part is OK, false if it is broken.
     */
    bool GetPartState(){
        return this->partState;
    }

    /*!
     * \brief Updates the operational state of the part.
     * \param state The new state to assign (true = OK, false = broken).
     */
    void updateState(bool state){
        this->partState = state;
    }
};

#endif // PART_H
