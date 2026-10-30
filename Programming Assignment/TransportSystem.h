#pragma once

#include "CityComponent.h"

class TransportSystem : public CityComponent
{
private:
    int trafficFlow;

public:
    TransportSystem(int id, const std::string& name, int flow);
    ~TransportSystem() override;

    void manageTraffic();
    void processEvent(const std::string& event) override;
};
