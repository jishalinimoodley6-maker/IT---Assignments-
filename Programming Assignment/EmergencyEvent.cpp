#include "EmergencyEvent.h"
#include <iostream>

EmergencyEvent::EmergencyEvent(int id,
                               const std::string& emergencyType,
                               int emergencySeverity)
    : emergencyID(id),
      type(emergencyType),
      severity(emergencySeverity)
{
}

int EmergencyEvent::getEmergencyID() const
{
    return emergencyID;
}

std::string EmergencyEvent::getType() const
{
    return type;
}

int EmergencyEvent::getSeverity() const
{
    return severity;
}

void EmergencyEvent::display() const
{
    std::cout << " Emergency ID: " << emergencyID
              << "  Type: " << type
              << "  Severity: " << severity
              << std::endl;
}
