#include "Report.h"
#include <iostream>
#include <map>
#include <iomanip>

void Report::generate(const EventProcessor& processor,
                      const CityData& cityData)
{
    const std::vector<Event>& events = processor.getProcessedEvents();

    std::cout << "\n THE SYSTEM REPORT " << std::endl;

    std::cout << "Total events that have been processed: "
              << processor.getTotalProcessed() << std::endl;

    std::map<std::string, int> emergencyCounts;

    const std::vector<EmergencyEvent> emergencies =
        processor.getEmergencies();

    for (std::vector<EmergencyEvent>::const_iterator it = emergencies.begin();
         it != emergencies.end(); ++it)
    {
        emergencyCounts[it->getType()]++;
    }

    std::string mostCommon = "None";
    int highestCount = 0;

    for (std::map<std::string, int>::const_iterator it = emergencyCounts.begin();
         it != emergencyCounts.end(); ++it)
    {
        if (it->second > highestCount)
        {
            highestCount = it->second;
            mostCommon = it->first;
        }
    }

    std::cout << "Most common emergency type: "
              << mostCommon << std::endl;

    double totalResponse = 0.0;

    for (std::vector<Event>::const_iterator it = events.begin();
         it != events.end(); ++it)
    {
        totalResponse += it->getResponseTime();
    }

    double averageResponse = 0.0;

    if (!events.empty())
    {
        averageResponse = totalResponse / events.size();
    }

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Average response time: "
              << averageResponse << " seconds" << std::endl;

    std::cout << "System load summary: "
              << events.size() << " processed events and "
              << cityData.getSensorReadings().size()
              << " sensor readings." << std::endl;

    std::cout << "---------------------------------" << std::endl;
}
