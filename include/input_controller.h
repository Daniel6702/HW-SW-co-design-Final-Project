#pragma once
#include <chrono>
#include "input_devices.h"
using namespace std::chrono;

class DataRetriever {
private:
    Sensor sensor1, sensor2;
    Camera camera;
    steady_clock::time_point lastSensorSample;
    steady_clock::time_point lastCameraSample;
    vector<int> sensorData = {0, 0};
    vector<vector<int>> cameraData = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    const milliseconds SENSOR_SAMPLE_INTERVAL = milliseconds(60);
    const milliseconds CAMERA_SAMPLE_INTERVAL = milliseconds(120);

    bool isTimeToSample(const steady_clock::time_point& lastSampleTime, const milliseconds& interval) {
        return duration_cast<milliseconds>(steady_clock::now() - lastSampleTime) >= interval;
    }

    void updateSensors() {
        sensorData[0] = sensor1.sampleData();
        sensorData[1] = sensor2.sampleData();
        lastSensorSample = steady_clock::now();
    }

    void updateCamera() {
        cameraData = camera.sampleData();
        lastCameraSample = steady_clock::now();
    }

public:
    DataRetriever() : lastSensorSample(steady_clock::now()), lastCameraSample(steady_clock::now()) {}

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
