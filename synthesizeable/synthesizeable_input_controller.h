#pragma once
#include "input_devices.h"

//volatile unsigned long long currentCycle = 0;


class DataRetriever {
private:
    Sensor sensor1, sensor2;
    Camera camera;
    unsigned long lastSensorSample;
    unsigned long lastCameraSample;
    vector<int> sensorData = {0, 0};
    vector<vector<int>> cameraData = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    const unsigned long SENSOR_SAMPLE_INTERVAL = 60; // Assuming these are clock cycles
    const unsigned long CAMERA_SAMPLE_INTERVAL = 120;

    bool isTimeToSample(unsigned long lastSampleTime, unsigned long interval, unsigned long currentCycle) {
        return (currentCycle - lastSampleTime) >= interval;
    }

    void updateSensors() {
        sensorData[0] = sensor1.sampleData();
        sensorData[1] = sensor2.sampleData();
        lastSensorSample = currentCycle;
    }

    void updateCamera() {
        cameraData = camera.sampleData();
        lastCameraSample = currentCycle;
    }

public:
    DataRetriever(unsigned long initialCycle)
        : lastSensorSample(initialCycle), lastCameraSample(initialCycle) {}

    void update(unsigned long currentCycle) {
        if (isTimeToSample(lastSensorSample, SENSOR_SAMPLE_INTERVAL, currentCycle)) {
            updateSensors();
        }
        if (isTimeToSample(lastCameraSample, CAMERA_SAMPLE_INTERVAL, currentCycle)) {
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
