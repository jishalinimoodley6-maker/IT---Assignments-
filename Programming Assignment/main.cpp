#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <limits>

#include "Engineer.h"
#include "CityData.h"
#include "EventProcessor.h"
#include "PowerSystem.h"
#include "TransportSystem.h"
#include "HealthSystem.h"
#include "SecuritySystem.h"
#include "FileManager.h"
#include "Report.h"

using namespace std;

void loadSampleData(vector<Engineer>& engineers,
                    CityData& cityData,
                    EventProcessor& processor)
{
    engineers.push_back(
        Engineer("ENG001", "admin", "admin123", "High")
    );

    engineers.push_back(
        Engineer("ENG002", "engineer", "eng123", "Medium")
    );

    engineers.push_back(
        Engineer("ENG003", "junior", "junior123", "Low")
    );

    cityData.addSensorReading(72.5);
    cityData.addSensorReading(65.3);
    cityData.addSensorReading(88.7);
    cityData.addSensorReading(54.2);
    cityData.addSensorReading(91.6);

    cityData.addHistoricalLog("Energy usage checked.");
    cityData.addHistoricalLog("Traffic density updated.");
    cityData.addHistoricalLog("Weather alert received.");

    processor.addEvent(Event(1, "Traffic accident", 3, 12.5, true));
    processor.addEvent(Event(2, "Power failure", 5, 8.2, true));
    processor.addEvent(Event(3, "Network overload", 2, 15.7, false));
    processor.addEvent(Event(4, "Weather alert", 4, 10.1, true));

    processor.addEmergency(
        EmergencyEvent(101, "Power failure", 5)
    );

    processor.addEmergency(
        EmergencyEvent(102, "Traffic accident", 4)
    );
}

bool login(const vector<Engineer>& engineers, Engineer& loggedInEngineer)
{
    string username;
    string password;

    
    cout << "    *** NEOVERSE LOGIN SYSTEM **" << endl;
    

    cout << "Username: ";
    cin >> username;

    cout << "Password: ";
    cin >> password;

    vector<Engineer>::const_iterator result =
        find_if(
            engineers.begin(),
            engineers.end(),
            [&](const Engineer& engineer)
            {
                return engineer.checkLogin(username, password);
            }
        );

    if (result != engineers.end())
    {
        loggedInEngineer = *result;

        cout << "\nLogin successful!" << endl;
        cout << "Engineer ID: "
             << result->getEngineerID() << endl;
        cout << "Clearance Level: "
             << result->getClearanceLevel() << endl;

        return true;
    }

    cout << "\nInvalid username or password." << endl;
    return false;
}

void showAlgorithms(CityData& cityData,
                    EventProcessor& processor)
{
    cout << "\n THE STL ALGORITHMS " << endl;

    cityData.sortSensorData();

    cout << "Sorted sensor data:" << endl;
    const vector<double>& readings = cityData.getSensorReadings();

    for (vector<double>::const_iterator it = readings.begin();
         it != readings.end(); ++it)
    {
        cout << *it << " ";
    }

    cout << "\nLowest sensor value: "
         << cityData.getLowestReading() << endl;

    cout << "Highest sensor value: "
         << cityData.getHighestReading() << endl;

    processor.filterCriticalEvents();

    int searchID;

    cout << "Enter event ID to search for: ";
    cin >> searchID;

    processor.findEventByID(searchID);

    cout << "\nAlgorithm Big-O:" << endl;
    cout << "sort        : O(n log n)" << endl;
    cout << "find/find_if : O(n)" << endl;
    cout << "min_element : O(n)" << endl;
    cout << "max_element : O(n)" << endl;
    cout << "count_if    : O(n)" << endl;
}

void showOOPDemo()
{
    cout << "\n OOP CITY ARCHITECTURE " << endl;

    vector<unique_ptr<CityComponent>> components;

    components.push_back(
        make_unique<PowerSystem>(1, "Main Power Grid", 85.0)
    );

    components.push_back(
        make_unique<TransportSystem>(2, "City Transport Network", 1200)
    );

    components.push_back(
        make_unique<HealthSystem>(3, "City Health Network", 5)
    );

    components.push_back(
        make_unique<SecuritySystem>(4, "City Security Network", 2)
    );

    for (vector<unique_ptr<CityComponent>>::iterator it = components.begin();
         it != components.end(); ++it)
    {
        (*it)->activate();

        cout << "\nComponent: " << (*it)->getName() << endl;
        cout << "Status: " << (*it)->getStatus() << endl;

        (*it)->processEvent("City system status check");
    }
}

int main()
{
    vector<Engineer> engineers;
    CityData cityData;
    EventProcessor processor;

    loadSampleData(engineers, cityData, processor);

    FileManager::saveEngineers(engineers, "engineers.dat");
    FileManager::saveLogs(cityData, "city_logs.dat");
    FileManager::saveConfig("config.txt");

    Engineer loggedIn("", "", "", "");

    bool loggedInSuccessfully = false;

    for (int attempts = 0; attempts < 3 && !loggedInSuccessfully; ++attempts)
    {
        loggedInSuccessfully = login(engineers, loggedIn);
    }

    if (!loggedInSuccessfully)
    {
        cout << "\nAccess has been denied. Maximum login attempts reached." << endl;
        return 0;
    }

    int choice = 0;

    do
    {
        cout << "\n\n================ NEOVERSE CITY SYSTEM ================" << endl;
        cout << "Logged in as: " << loggedIn.getUsername() << endl;
        cout << "Clearance: " << loggedIn.getClearanceLevel() << endl;
       
        cout << "1. Display the city data" << endl;
        cout << "2. Display the pending events" << endl;
        cout << "3. Process the next event" << endl;
        cout << "4. Display the emergency stack" << endl;
        cout << "5. Resolve the latest emergency" << endl;
        cout << "6. Run the STL algorithms" << endl;
        cout << "7. Demonstrate the OOP architecture" << endl;
        cout << "8. Generate the system report" << endl;
        cout << "9. Savethe system data" << endl;
        cout << "10. Adda  new event" << endl;
        cout << "11. Add a emergency override" << endl;
        cout << "12. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            cityData.displaySensorReadings();
            cityData.displayHistoricalLogs();
        }
        else if (choice == 2)
        {
            processor.displayPendingEvents();
        }
        else if (choice == 3)
        {
            processor.processNextEvent();
        }
        else if (choice == 4)
        {
            processor.displayEmergencies();
        }
        else if (choice == 5)
        {
            processor.resolveLatestEmergency();
        }
        else if (choice == 6)
        {
            showAlgorithms(cityData, processor);
        }
        else if (choice == 7)
        {
            showOOPDemo();
        }
        else if (choice == 8)
        {
            Report::generate(processor, cityData);
        }
        else if (choice == 9)
        {
            FileManager::saveEngineers(engineers, "engineers.dat");
            FileManager::saveEvents(processor.getProcessedEvents(),
                                    "events.dat");
            FileManager::saveLogs(cityData, "city_logs.dat");
            FileManager::saveConfig("config.txt");

            cout << "System data is saved successfully." << endl;
        }
        else if (choice == 10)
        {
            int id;
            int priority;
            double responseTime;
            int criticalValue;
            string type;

            cout << "Enter the event ID: ";
            cin >> id;

            cout << "Enter the event type: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, type);

            cout << "Enter your priority: ";
            cin >> priority;

            cout << "Enter your response time: ";
            cin >> responseTime;

            cout << "Critical event? (1 = Yes, 0 = No): ";
            cin >> criticalValue;

            processor.addEvent(
                Event(id, type, priority, responseTime,
                      criticalValue == 1)
            );

            cout << "Event added to the queue." << endl;
        }
        else if (choice == 11)
        {
            int id;
            int severity;
            string type;

            cout << "Enter the emergency ID: ";
            cin >> id;

            cout << "Enter the emergency type: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, type);

            cout << "Enter the severity: ";
            cin >> severity;

            processor.addEmergency(
                EmergencyEvent(id, type, severity)
            );

            cout << "Emergency override added to the stack." << endl;
        }
        else if (choice == 12)
        {
            cout << "\nExiting the NeoVerse system..." << endl;
        }
        else
        {
            cout << "Invalid choice." << endl;
        }

    } while (choice != 12);

    return 0;
}
