#include "HealthSystem.h"
#include <iostream>

HealthSystem::HealthSystem(int id, const std::string& name, int hospitals)
    : CityComponent(id, name),
      hospitalCnt(hospitals)
{
}

HealthSystem::~HealthSystem()
{
}

void HealthSystem::provideCare()
{
    std::cout << getName() << " has "
              << hospitalCnt << " hospitals that are available." << std::endl;
}

void HealthSystem::processEvent(const std::string& event)
{
    std::cout << "HealthSystem is processing the event: "
              << event << std::endl;
}
