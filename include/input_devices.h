#pragma once
#include <cstdlib> 
#include <vector>
using namespace std;

template<typename T>
class InputDevice {
protected:
    unsigned int lfsr = 0xACE1u;
    unsigned bit;
    unsigned lfsrRand() { //synthesizable rand function
        bit  = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5) ) & 1;
        return lfsr =  (lfsr >> 1) | (bit << 15);
    }
public:
    virtual ~InputDevice() {}
    virtual T sampleData() = 0;
};

class Sensor : public InputDevice<int> {
public:
    int sampleData() override {
        return lfsrRand() % 6;
    }
};

class Camera : public InputDevice<vector<vector<int>>> {
public:
    vector<vector<int>> sampleData() override {
        vector<vector<int>> matrix(9, vector<int>(9));
        for (auto& row : matrix) {
            for (int& value : row) {
                value = lfsrRand() % 10;
            }
        }
        return matrix;
    }
};
