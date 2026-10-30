#pragma once

#include "CityComponent.h"

class HealthSystem : public CityComponent
{
private:
    int hospitalCnt;

public:
    HealthSystem(int id, const std::string& name, int hospitals);
    ~HealthSystem() override;

    void provideCare();
    void processEvent(const std::string& event) override;
};
