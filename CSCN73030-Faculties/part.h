#ifndef PART_H
#define PART_H

#include <string>

class Part
{
private:
    std::string partType;
    std::string aquisitionDate;
    int partID;
    std::string partDescription;
    enum States{
        OK,
        BROKEN
    };
    enum States partState;

public:
    Part();
    Part(std::string partType, std::string aquisitionDate, int partID, std::string partDescription);

    std::string GetPartType(){
        return this->partType;
    }

    void SetPartType(std::string partType){
        this->partType = partType;
    }

    std::string GetAquisitionDate(){
        return this->aquisitionDate;
    }

    void SetAquisitionDate(std::string partType){
        this->partType = partType;
    }

    int GetPartID(){
        return this->partID;
    }

    void SetPartID(int partID){
        this->partID = partID;
    }

    std::string GetPartDesc(){
        return this->partDescription;
    }

    void SetPartDesc(std::string partDesc){
        this->partDescription = partDesc;
    }

    bool getPartState(){
        return this->partState;
    }

    void updateState(bool state){
        if(state == 1)
            this->partState = OK;
        else if (state == 0)
            this->partState = BROKEN;
    }
};

#endif // PART_H
