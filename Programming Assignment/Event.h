#pragma once

#include <string>

class Event
{
private:
    int eventID;
    std::string type;
    int priority;
    double responseTime;
    bool critical;

public:
    Event(int id = 0,
          const std::string& eventType = "",
          int eventPriority = 0,
          double time = 0.0,
          bool isCritical = false);

    int getEventID() const;
    std::string getType() const;
    int getPriority() const;
    double getResponseTime() const;
    bool isCritical() const;

    void display() const;
};
