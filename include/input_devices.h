#pragma once
#include <cstdlib> 
#include <vector>
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
