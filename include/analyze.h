#pragma once
#include "events.h"
#include <iostream>
using namespace std;

class AnalysisModule {
private:
    bool checkIntrusion(const vector<int>& sensorData, const vector<std::vector<int>>& cameraData) {
        int sum = 0;
        int sensorSum = sensorData[0] + sensorData[1];
        
        for (const auto& row : cameraData) {
            for (int value : row) {
                sum += sensorSum * value;
            }
        }
        cout << "sum: " << sum << endl;
        return sum >= 6290;
    }

public:
    Event analyze(const vector<int>& sensorData, const vector<vector<int>>& cameraData) {
        if (checkIntrusion(sensorData, cameraData)) {
            return Trigger;
        }
        return NoEvent;
    }
};
