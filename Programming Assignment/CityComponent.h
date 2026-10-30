#pragma once

#include <string>

class CityComponent
{
private:
    int componentID;
    std::string name;
    bool active;

public:
    CityComponent(int id, const std::string& componentName);
    virtual ~CityComponent();

    void activate();
    void deactivate();
    std::string getStatus() const;

    int getComponentID() const;
    std::string getName() const;

    virtual void processEvent(const std::string& event) = 0;
};
