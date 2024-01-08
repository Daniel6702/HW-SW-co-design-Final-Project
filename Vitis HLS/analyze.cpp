#include "..\\include\\analyze.h"
using namespace std;

#define SENSOR_SIZE 2
#define CAMERA_ROWS 9
#define CAMERA_COLS 9


#define CHECK_INTRUSION_BASE_ADDR 0x43C00000
#define CONTROL_OFFSET 0x00
#define GIER_OFFSET 0x04
#define IP_IER_OFFSET 0x08
#define IP_ISR_OFFSET 0x0C
#define RESULT_OFFSET 0x10
#define SENSOR_DATA_OFFSET 0x14
#define CAMERA_DATA_OFFSET 0x18

bool checkIntrusion_hw(const int sensorData[SENSOR_SIZE], const int cameraData[CAMERA_ROWS][CAMERA_COLS]) {
    #pragma HLS INTERFACE s_axilite port=return bundle=CTRL_BUS
    #pragma HLS INTERFACE s_axilite port=sensorData bundle=CTRL_BUS
    #pragma HLS INTERFACE s_axilite port=cameraData bundle=CTRL_BUS
    #pragma HLS INTERFACE ap_ctrl_hs port=return bundle=CTRL_BUS

    static bool intrusion;
    #pragma HLS INTERFACE ap_none port=intrusion

    int sum = 0;
    int sensorSum = sensorData[0] + sensorData[1];
    #pragma HLS ARRAY_PARTITION variable=cameraData complete dim=2
    for (int i = 0; i < CAMERA_ROWS; ++i) {
        for (int j = 0; j < CAMERA_COLS; ++j) {
            sum += sensorSum * cameraData[i][j];
        }
    }
    intrusion = sum >= 6290;
    return intrusion;
}

bool AnalysisModule::checkIntrusion(const vector<int>& sensorDataVec, const vector<std::vector<int>>& cameraDataVec) {
    int sensorData[SENSOR_SIZE];
    for (size_t i = 0; i < SENSOR_SIZE; ++i) {
        sensorData[i] = sensorDataVec[i];
    }
    int cameraData[CAMERA_ROWS][CAMERA_COLS];
    for (size_t i = 0; i < CAMERA_ROWS; ++i) {
        for (size_t j = 0; j < CAMERA_COLS; ++j) {
            cameraData[i][j] = cameraDataVec[i][j];
        }
    }
    return checkIntrusion_hw(sensorData,cameraData);
}

Event AnalysisModule::analyze(const vector<int>& sensorData, const vector<std::vector<int>>& cameraData) {
    if (checkIntrusion(sensorData, cameraData)) {
        return Trigger;
    }
    return NoEvent;
}
