#include "PowerSystem.h"
#include <iostream>

PowerSystem::PowerSystem(int id, const std::string& name, double level)
    : CityComponent(id, name),
      powerLevel(level)
{
}

PowerSystem::~PowerSystem()
{
}

void PowerSystem::supplyPower()
{
    std::cout << getName() << " is supplying power at "
              << powerLevel << "% capacity." << std::endl;
}

void PowerSystem::processEvent(const std::string& event)
{
    std::cout << "PowerSystem is processing the event: "
              << event << std::endl;
}
