#include "EventProcessor.h"
#include <iostream>
#include <algorithm>

void EventProcessor::addEvent(const Event& event)
{
    eventQueue.push(event);
}

void EventProcessor::processNextEvent()
{
    if (eventQueue.empty())
    {
        std::cout << "No events waiting to be processed." << std::endl;
        return;
    }

    Event event = eventQueue.front();
    eventQueue.pop();

    processedEvents.push_back(event);

    std::cout << "\nProcessing the event:" << std::endl;
    event.display();
}

void EventProcessor::displayPendingEvents() const
{
    if (eventQueue.empty())
    {
        std::cout << "No pending events." << std::endl;
        return;
    }

    std::queue<Event> copy = eventQueue;

    std::cout << "\nEvents Pending (FIFO):" << std::endl;

    while (!copy.empty())
    {
        copy.front().display();
        copy.pop();
    }
}

void EventProcessor::addEmergency(const EmergencyEvent& emergency)
{
    emergencyStack.push(emergency);
}

void EventProcessor::resolveLatestEmergency()
{
    if (emergencyStack.empty())
    {
        std::cout << "No emergency overrides." << std::endl;
        return;
    }

    std::cout << "\nResolving the latest emergency:" << std::endl;
    emergencyStack.top().display();
    emergencyStack.pop();
}

void EventProcessor::displayEmergencies() const
{
    if (emergencyStack.empty())
    {
        std::cout << "No emergency overrides." << std::endl;
        return;
    }

    std::stack<EmergencyEvent> copy = emergencyStack;

    std::cout << "\n The Emergency Stack (LIFO):" << std::endl;

    while (!copy.empty())
    {
        copy.top().display();
        copy.pop();
    }
}

void EventProcessor::filterCriticalEvents() const
{
    int criticalCount = static_cast<int>(
        std::count_if(
            processedEvents.begin(),
            processedEvents.end(),
            [](const Event& event)
            {
                return event.isCritical();
            }
        )
    );

    std::cout << " The Critical processed events: "
              << criticalCount << std::endl;
}

void EventProcessor::findEventByID(int id) const
{
    std::vector<Event>::const_iterator result =
        std::find_if(
            processedEvents.begin(),
            processedEvents.end(),
            [id](const Event& event)
            {
                return event.getEventID() == id;
            }
        );

    if (result != processedEvents.end())
    {
        std::cout << "Event has been found:" << std::endl;
        result->display();
    }
    else
    {
        std::cout << "Event has not found." << std::endl;
    }
}

int EventProcessor::getTotalProcessed() const
{
    return static_cast<int>(processedEvents.size());
}

const std::vector<Event>& EventProcessor::getProcessedEvents() const
{
    return processedEvents;
}

const std::stack<EmergencyEvent>& EventProcessor::getEmergencyStack() const
{
    return emergencyStack;
}

std::vector<Event> EventProcessor::getPendingEvents() const
{
    std::vector<Event> events;
    std::queue<Event> copy = eventQueue;

    while (!copy.empty())
    {
        events.push_back(copy.front());
        copy.pop();
    }

    return events;
}

std::vector<EmergencyEvent> EventProcessor::getEmergencies() const
{
    std::vector<EmergencyEvent> emergencies;
    std::stack<EmergencyEvent> copy = emergencyStack;

    while (!copy.empty())
    {
        emergencies.push_back(copy.top());
        copy.pop();
    }

    std::reverse(emergencies.begin(), emergencies.end());

    return emergencies;
}
