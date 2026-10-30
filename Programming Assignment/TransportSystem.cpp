#include "TransportSystem.h"
#include <iostream>

TransportSystem::TransportSystem(int id, const std::string& name, int flow)
    : CityComponent(id, name),
      trafficFlow(flow)
{
}

TransportSystem::~TransportSystem()
{
}

void TransportSystem::manageTraffic()
{
    std::cout << getName() << " is managing traffic flow of "
              << trafficFlow << " vehicles/hour." << std::endl;
}

void TransportSystem::processEvent(const std::string& event)
{
    std::cout << "TransportSystem is processing the event: "
              << event << std::endl;
}
