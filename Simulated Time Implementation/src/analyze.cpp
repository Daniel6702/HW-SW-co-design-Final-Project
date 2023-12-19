#include "..\\include\\analyze.h"
using namespace std;

bool AnalysisModule::checkIntrusion(const vector<int>& sensorData, const vector<std::vector<int>>& cameraData) {
    int sum = 0;
    int sensorSum = sensorData[0] + sensorData[1];
    
    for (const auto& row : cameraData) {
        for (int value : row) {
            sum += sensorSum * value;
        }
    }
    //cout << "sum: " << sum << endl;
    return sum >= 6290;
}

Event AnalysisModule::analyze(const vector<int>& sensorData, const vector<std::vector<int>>& cameraData) {
    if (checkIntrusion(sensorData, cameraData)) {
        return Trigger;
    }
    return NoEvent;
}
