#pragma once
#include <chrono>
#include <thread>
#include "input.h"
#include "events.h"
using namespace std::chrono;

class AlarmSystem;

class AnalysisModule {
private:
    Sensor s1, s2;
    Camera c;
    steady_clock::time_point lastSensorSample;
    steady_clock::time_point lastCameraSample;

    void sampleSensors() {
    }

    void sampleCamera() {
    }

    bool checkIntrusion() {
    }

public:
    AnalysisModule() : lastSensorSample(steady_clock::now()),
                       lastCameraSample(steady_clock::now()) {}
    void update(AlarmSystem& alarmSystem); 
};
