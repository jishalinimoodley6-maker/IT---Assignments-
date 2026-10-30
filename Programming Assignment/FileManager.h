#pragma once

#include "Engineer.h"
#include "Event.h"
#include "EmergencyEvent.h"
#include "CityData.h"
#include <vector>
#include <string>

class FileManager
{
public:
    static void saveEngineers(const std::vector<Engineer>& engineers,
                              const std::string& filename);

    static std::vector<Engineer> loadEngineers(
        const std::string& filename);

    static void saveEvents(const std::vector<Event>& events,
                           const std::string& filename);

    static std::vector<Event> loadEvents(
        const std::string& filename);

    static void saveLogs(const CityData& cityData,
                         const std::string& filename);

    static void loadLogs(CityData& cityData,
                         const std::string& filename);

    static void saveConfig(const std::string& filename);
};
