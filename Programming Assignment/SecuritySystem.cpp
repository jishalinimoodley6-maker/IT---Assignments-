#include "SecuritySystem.h"
#include <iostream>

SecuritySystem::SecuritySystem(int id, const std::string& name, int level)
    : CityComponent(id, name),
      threatLevel(level)
{
}

SecuritySystem::~SecuritySystem()
{
}

void SecuritySystem::monitorCity()
{
    std::cout << getName() << " is monitoring the city. Threat level: "
              << threatLevel << std::endl;
}

void SecuritySystem::processEvent(const std::string& event)
{
    std::cout << "SecuritySystem is processing the event: "
              << event << std::endl;
}
