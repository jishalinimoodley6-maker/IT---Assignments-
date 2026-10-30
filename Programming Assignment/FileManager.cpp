#include "FileManager.h"
#include <fstream>
#include <sstream>
#include <iostream>

void FileManager::saveEngineers(
    const std::vector<Engineer>& engineers,
    const std::string& filename)
{
    std::ofstream file(filename);

    if (!file)
    {
        std::cout << "Could not open  " << filename << " for writing." << std::endl;
        return;
    }

    for (std::vector<Engineer>::const_iterator it = engineers.begin();
         it != engineers.end(); ++it)
    {
        file << it->getEngineerID() << "|"
             << it->getUsername() << "|"
             << it->getEncryptedPassword() << "|"
             << it->getClearanceLevel() << "\n";
    }
}

std::vector<Engineer> FileManager::loadEngineers(
    const std::string& filename)
{
    std::vector<Engineer> engineers;
    std::ifstream file(filename);

    if (!file)
    {
        return engineers;
    }

    std::string line;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string id, user, password, clearance;

        std::getline(ss, id, '|');
        std::getline(ss, user, '|');
        std::getline(ss, password, '|');
        std::getline(ss, clearance, '|');

        if (!id.empty())
        {
            engineers.push_back(
                Engineer(id, user, password, clearance)
            );
        }
    }

    return engineers;
}

void FileManager::saveEvents(
    const std::vector<Event>& events,
    const std::string& filename)
{
    std::ofstream file(filename);

    if (!file)
    {
        std::cout << "Could not open " << filename << " for writing." << std::endl;
        return;
    }

    for (std::vector<Event>::const_iterator it = events.begin();
         it != events.end(); ++it)
    {
        file << it->getEventID() << "|"
             << it->getType() << "|"
             << it->getPriority() << "|"
             << it->getResponseTime() << "|"
             << it->isCritical() << "\n";
    }
}

std::vector<Event> FileManager::loadEvents(
    const std::string& filename)
{
    std::vector<Event> events;
    std::ifstream file(filename);

    if (!file)
    {
        return events;
    }

    std::string line;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string id, type, priority, responseTime, critical;

        std::getline(ss, id, '|');
        std::getline(ss, type, '|');
        std::getline(ss, priority, '|');
        std::getline(ss, responseTime, '|');
        std::getline(ss, critical, '|');

        if (!id.empty())
        {
            events.push_back(
                Event(
                    std::stoi(id),
                    type,
                    std::stoi(priority),
                    std::stod(responseTime),
                    std::stoi(critical) != 0
                )
            );
        }
    }

    return events;
}

void FileManager::saveLogs(
    const CityData& cityData,
    const std::string& filename)
{
    std::ofstream file(filename);

    if (!file)
    {
        std::cout << "Could not open " << filename << " for writing." << std::endl;
        return;
    }

    file << " THE SENSOR_READINGS\n";

    const std::vector<double>& readings = cityData.getSensorReadings();

    for (std::vector<double>::const_iterator it = readings.begin();
         it != readings.end(); ++it)
    {
        file << *it << "\n";
    }

    file << "THE HISTORICAL_LOGS\n";

    const std::list<std::string>& logs = cityData.getHistoricalLogs();

    for (std::list<std::string>::const_iterator it = logs.begin();
         it != logs.end(); ++it)
    {
        file << *it << "\n";
    }
}

void FileManager::loadLogs(
    CityData& cityData,
    const std::string& filename)
{
    std::ifstream file(filename);

    if (!file)
    {
        return;
    }

    std::string line;
    bool readingSensors = false;
    bool readingLogs = false;

    while (std::getline(file, line))
    {
        if (line == " THE SENSOR_READINGS")
        {
            readingSensors = true;
            readingLogs = false;
        }
        else if (line == " THE HISTORICAL_LOGS")
        {
            readingSensors = false;
            readingLogs = true;
        }
        else if (readingSensors && !line.empty())
        {
            cityData.addSensorReading(std::stod(line));
        }
        else if (readingLogs && !line.empty())
        {
            cityData.addHistoricalLog(line);
        }
    }
}

void FileManager::saveConfig(const std::string& filename)
{
    std::ofstream file(filename);

    if (!file)
    {
        std::cout << "Could not open " << filename << " for writing." << std::endl;
        return;
    }

    file << "NeoVerse Configuration\n";
    file << "System=AI City Survival Engine\n";
    file << "Version=1.0\n";
    file << "Search=Linear find_if\n";
    file << "DefaultClearance=Medium\n";
}
