#pragma once

#include "CityComponent.h"

class SecuritySystem : public CityComponent
{
private:
    int threatLevel;

public:
    SecuritySystem(int id, const std::string& name, int level);
    ~SecuritySystem() override;

    void monitorCity();
    void processEvent(const std::string& event) override;
};
