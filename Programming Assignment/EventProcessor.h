#pragma once

#include "Event.h"
#include "EmergencyEvent.h"
#include <queue>
#include <stack>
#include <vector>

class EventProcessor
{
private:
    std::queue<Event> eventQueue;
    std::stack<EmergencyEvent> emergencyStack;
    std::vector<Event> processedEvents;

public:
    void addEvent(const Event& event);
    void processNextEvent();
    void displayPendingEvents() const;

    void addEmergency(const EmergencyEvent& emergency);
    void resolveLatestEmergency();
    void displayEmergencies() const;

    void filterCriticalEvents() const;
    void findEventByID(int id) const;

    int getTotalProcessed() const;
    const std::vector<Event>& getProcessedEvents() const;
    const std::stack<EmergencyEvent>& getEmergencyStack() const;

    std::vector<Event> getPendingEvents() const;
    std::vector<EmergencyEvent> getEmergencies() const;
};
