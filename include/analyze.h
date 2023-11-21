#pragma once
#include "events.h"
#include "signal.h"
#include <iostream>
using namespace std;

class AnalysisModule {
private:
    vector<int> sensorData = {0, 0};
    vector<vector<int>> cameraData = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

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
    Signal<Event> signal;

    AnalysisModule() {}

    void processSensorData(const std::vector<int>& data) {
        sensorData = data;
    }

    void processCameraData(const std::vector<std::vector<int>>& data) {
        cameraData = data;
    }

    void update() {
        if (checkIntrusion(sensorData, cameraData)) {
            signal.emit(Trigger);
        }
    }
};
