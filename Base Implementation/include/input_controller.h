#pragma once
#include "input_devices.h"
#include "simulated_clock.h"
#include <vector>

using std::vector;

class DataRetriever {
private:
    Sensor sensor1, sensor2;
    Camera camera;
    uint64_t lastSensorSample;
    uint64_t lastCameraSample;
    vector<int> sensorData = {0, 0};
    vector<vector<int>> cameraData = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    const uint64_t SENSOR_SAMPLE_INTERVAL = 60; // milliseconds
    const uint64_t CAMERA_SAMPLE_INTERVAL = 120; // milliseconds

    bool isTimeToSample(uint64_t lastSampleTime, uint64_t interval) {
        return (SimulatedClock::now() - lastSampleTime) >= interval;
    }

    void updateSensors() {
        sensorData[0] = sensor1.sampleData();
        sensorData[1] = sensor2.sampleData();
        lastSensorSample = SimulatedClock::now();
    }

    void updateCamera() {
        cameraData = camera.sampleData();
        lastCameraSample = SimulatedClock::now();
    }

public:
    DataRetriever() : lastSensorSample(SimulatedClock::now()), lastCameraSample(SimulatedClock::now()) {}

    void update() {
        if (isTimeToSample(lastSensorSample, SENSOR_SAMPLE_INTERVAL)) {
            updateSensors();
        }
        if (isTimeToSample(lastCameraSample, CAMERA_SAMPLE_INTERVAL)) {
            updateCamera();
        }
    }

    const vector<int>& getSensorData() const {
        return sensorData;
    }

    const vector<vector<int>>& getCameraData() const {
        return cameraData;
    }
};
