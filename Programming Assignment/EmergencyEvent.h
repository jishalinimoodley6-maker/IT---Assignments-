#pragma once

#include <string>

class EmergencyEvent
{
private:
    int emergencyID;
    std::string type;
    int severity;

public:
    EmergencyEvent(int id = 0,
                   const std::string& emergencyType = "",
                   int emergencySeverity = 0);

    int getEmergencyID() const;
    std::string getType() const;
    int getSeverity() const;

    void display() const;
};
