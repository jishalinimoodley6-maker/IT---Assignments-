#pragma once

#include "EventProcessor.h"
#include "CityData.h"

class Report
{
public:
    static void generate(const EventProcessor& processor,
                         const CityData& cityData);
};
