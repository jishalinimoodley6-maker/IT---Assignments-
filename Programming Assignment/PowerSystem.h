#pragma once

#include "CityComponent.h"

class PowerSystem : public CityComponent
{
private:
    double powerLevel;

public:
    PowerSystem(int id, const std::string& name, double level);
    ~PowerSystem() override;

    void supplyPower();
    void processEvent(const std::string& event) override;
};
