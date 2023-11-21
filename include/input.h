#pragma once
#include <cstdlib> 
#include <vector>
#include <chrono>
#include "signal.h"
using namespace std::chrono;
using namespace std;

template<typename T>
class InputDevice {
public:
    virtual T sampleData() = 0;
    virtual ~InputDevice() {}
};

class Sensor : public InputDevice<int> {
public:
    int sampleData() override {
        return rand() % 6; 
    }
};

class Camera : public InputDevice<vector<vector<int>>> {
public:
    vector<vector<int>> sampleData() override {
        vector<vector<int>> matrix(9,vector<int>(9));
        for (auto& row : matrix) {
            for (int& value : row) {
                value = rand() % 10;
            }
        }
        return matrix;
    }
};


class DataRetriever {
private:
    Sensor sensor1, sensor2;
    Camera camera;
    steady_clock::time_point lastSensorSample;
    steady_clock::time_point lastCameraSample;

public:
    Signal<vector<int>> sensorSignal;
    Signal<vector<vector<int>>> cameraSignal;

    DataRetriever() : 
        lastSensorSample(steady_clock::now()), 
        lastCameraSample(steady_clock::now()) {}

    void update() {
        auto now = steady_clock::now();
        if (duration_cast<milliseconds>(now - lastSensorSample).count() >= 60) {
            sensorSignal.emit({sensor1.sampleData(), sensor2.sampleData()});
            lastSensorSample = now;
        }
        if (duration_cast<milliseconds>(now - lastCameraSample).count() >= 120) {
            cameraSignal.emit(camera.sampleData());
            lastCameraSample = now;
        }
    }
};