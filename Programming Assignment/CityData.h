#pragma once

#include <vector>
#include <list>
#include <string>

class CityData
{
private:
    std::vector<double> sensorReadings;
    std::list<std::string> historicalLogs;

public:
    void addSensorReading(double reading);
    void removeOldestReading();
    void displaySensorReadings() const;

    void addHistoricalLog(const std::string& log);
    void removeOldestLog();
    void displayHistoricalLogs() const;

    const std::vector<double>& getSensorReadings() const;
    const std::list<std::string>& getHistoricalLogs() const;
    std::vector<double>& getSensorReadings();

    void sortSensorData();
    double getLowestReading() const;
    double getHighestReading() const;
};
