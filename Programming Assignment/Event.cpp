#include "Event.h"
#include <iostream>

Event::Event(int id,
             const std::string& eventType,
             int eventPriority,
             double time,
             bool isCriticalValue)
    : eventID(id),
      type(eventType),
      priority(eventPriority),
      responseTime(time),
      critical(isCriticalValue)
{
}

int Event::getEventID() const
{
    return eventID;
}

std::string Event::getType() const
{
    return type;
}

int Event::getPriority() const
{
    return priority;
}

double Event::getResponseTime() const
{
    return responseTime;
}

bool Event::isCritical() const
{
    return critical;
}

void Event::display() const
{
    std::cout << "Event ID: " << eventID
              << "  Type: " << type
              << "  Priority: " << priority
              << "  Response Time: " << responseTime << " second"
              << "  Critical: " << (critical ? "Yes" : "No")
              << std::endl;
}
