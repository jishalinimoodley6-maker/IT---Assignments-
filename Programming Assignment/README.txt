NEOVERSE: AI CITY SURVIVAL SYSTEM
Programming 622 Assignment

HOW TO RUN
1. Create a C++ project using C++17 or later.
2. Add all .cpp and .h files to the project.
3. Keep the .dat and config.txt files in the program working directory.
4. Compile all .cpp files together.
5. Run the program.

SAMPLE LOGIN CREDENTIALS
Username: admin
Password: admin123
Clearance: High

Other accounts:
Username: engineer
Password: eng123
Clearance: Medium

Username: junior
Password: junior123
Clearance: Low

CONTAINERS USED
- vector: engineers and daily sensor readings
- list: historical city logs
- queue: incoming events using FIFO
- stack: emergency overrides using LIFO
- vector: processed events

STL ALGORITHMS
- sort: O(n log n)
- find/find_if: O(n)
- min_element: O(n)
- max_element: O(n)
- count_if: O(n)

BIG-O DECISIONS
Vector provides constant-time indexed access, O(1), which makes it suitable
for daily sensor readings. Inserting at the end is normally amortized O(1),
while inserting/removing at the beginning is O(n).

A linked list supports insertion/removal at a known position in O(1), but
traversal is O(n) and random access is not available.

A queue is appropriate for normal city events because events are processed
in arrival order (FIFO).

A stack is appropriate for emergency overrides because the most recent
emergency is resolved first (LIFO).

The login implementation uses find_if(), which is O(n) in the worst case.
Binary search can be O(log n), but the data must be kept sorted according
to the search key.

FILES
Engineer.h / Engineer.cpp
Event.h / Event.cpp
EmergencyEvent.h / EmergencyEvent.cpp
CityData.h / CityData.cpp
EventProcessor.h / EventProcessor.cpp
CityComponent.h / CityComponent.cpp
PowerSystem.h / PowerSystem.cpp
TransportSystem.h / TransportSystem.cpp
HealthSystem.h / HealthSystem.cpp
SecuritySystem.h / SecuritySystem.cpp
FileManager.h / FileManager.cpp
Report.h / Report.cpp
main.cpp

DATA FILES
engineers.dat
events.dat
city_logs.dat
config.txt
