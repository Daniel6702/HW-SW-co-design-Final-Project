#pragma once
#include "events.h"
#include <vector>
#include <iostream>

class AnalysisModule {
public:
    bool checkIntrusion(const std::vector<int>& sensorData, const std::vector<std::vector<int>>& cameraData);
    Event analyze(const std::vector<int>& sensorData, const std::vector<std::vector<int>>& cameraData);
};
