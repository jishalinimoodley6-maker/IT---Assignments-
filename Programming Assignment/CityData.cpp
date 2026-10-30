#include "CityData.h"
#include <iostream>
#include <algorithm>
#include <stdexcept>

void CityData::addSensorReading(double reading)
{
    sensorReadings.push_back(reading);
}

void CityData::removeOldestReading()
{
    if (!sensorReadings.empty())
    {
        sensorReadings.erase(sensorReadings.begin());
    }
}

void CityData::displaySensorReadings() const
{
    std::cout << "\n The Daily Sensor Readings:" << std::endl;

    for (std::vector<double>::const_iterator it = sensorReadings.begin();
         it != sensorReadings.end(); ++it)
    {
        std::cout << *it << std::endl;
    }
}

void CityData::addHistoricalLog(const std::string& log)
{
    historicalLogs.push_back(log);
}

void CityData::removeOldestLog()
{
    if (!historicalLogs.empty())
    {
        historicalLogs.pop_front();
    }
}

void CityData::displayHistoricalLogs() const
{
    std::cout << "\n The Historical City Logs:" << std::endl;

    for (std::list<std::string>::const_iterator it = historicalLogs.begin();
         it != historicalLogs.end(); ++it)
    {
        std::cout << *it << std::endl;
    }
}

const std::vector<double>& CityData::getSensorReadings() const
{
    return sensorReadings;
}

const std::list<std::string>& CityData::getHistoricalLogs() const
{
    return historicalLogs;
}

std::vector<double>& CityData::getSensorReadings()
{
    return sensorReadings;
}

void CityData::sortSensorData()
{
    std::sort(sensorReadings.begin(), sensorReadings.end());
}

double CityData::getLowestReading() const
{
    if (sensorReadings.empty())
    {
        return 0.0;
    }

    return *std::min_element(sensorReadings.begin(), sensorReadings.end());
}

double CityData::getHighestReading() const
{
    if (sensorReadings.empty())
    {
        return 0.0;
    }

    return *std::max_element(sensorReadings.begin(), sensorReadings.end());
}
