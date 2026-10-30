#include "CityComponent.h"

CityComponent::CityComponent(int id, const std::string& componentName)
    : componentID(id),
      name(componentName),
      active(false)
{
}

CityComponent::~CityComponent()
{
}

void CityComponent::activate()
{
    active = true;
}

void CityComponent::deactivate()
{
    active = false;
}

std::string CityComponent::getStatus() const
{
    return active ? "Active" : "Inactive";
}

int CityComponent::getComponentID() const
{
    return componentID;
}

std::string CityComponent::getName() const
{
    return name;
}
