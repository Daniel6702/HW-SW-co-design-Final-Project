#include "..\\include\\analyze.h"
#include "xil_io.h"
#include "xparameters.h"
using namespace std;

#define SENSOR_SIZE 2
#define CAMERA_ROWS 9
#define CAMERA_COLS 9

#define IP_HIGH_ADDR XPAR_CHECKINTRUSION_0_HIGHADDR
#define IP_BASE_ADDR XPAR_CHECKINTRUSION_0_BASEADDR
#define CTRL_OFFSET 0x00
#define GIER_OFFSET 0x04
#define IER_OFFSET  0x08
#define ISR_OFFSET  0x0C
#define RETURN_OFFSET 0x10
#define SENSOR_DATA_OFFSET 0x24
#define CAMERA_DATA_OFFSET 0x512

bool checkIntrusion_hw(const vector<int>& sensorDataVec, const vector<std::vector<int>>& cameraDataVec) {

    // Convert sensorData to raw array
    int sensorData[SENSOR_SIZE];
    for (size_t i = 0; i < SENSOR_SIZE; ++i) {
        sensorData[i] = sensorDataVec[i];
    }

    // Convert cameraData to raw 2D array
    int cameraData[CAMERA_ROWS][CAMERA_COLS];
    for (size_t i = 0; i < CAMERA_ROWS; ++i) {
        for (size_t j = 0; j < CAMERA_COLS; ++j) {
            cameraData[i][j] = cameraDataVec[i][j];
        }
    }

    //Write sensor data to correct memory location
    for (int i = 0; i < SENSOR_SIZE; ++i) {
        Xil_Out32(IP_BASE_ADDR + SENSOR_DATA_OFFSET + (i * 4), sensorData[i]);
    }

    //Write camera data
    for (int i = 0; i < CAMERA_ROWS; ++i) {
        for (int j = 0; j < CAMERA_COLS; ++j) {
            // Calculate the offset for each element in the camera data matrix
            int offset = CAMERA_DATA_OFFSET + (i * CAMERA_COLS + j) * 4;
            Xil_Out32(IP_BASE_ADDR + offset, cameraData[i][j]);
        }
    }

    // Start the hardware function by writing to the CTRL register
    Xil_Out32(IP_BASE_ADDR + CTRL_OFFSET, 1);

    // Wait for the operation to complete
    while (!(Xil_In32(IP_BASE_ADDR + ISR_OFFSET) & 0x1)) {}

    // Read the result from the RETURN_OFFSET
    return Xil_In32(IP_BASE_ADDR + RETURN_OFFSET) != 0;
}

bool AnalysisModule::checkIntrusion(const vector<int>& sensorDataVec, const vector<std::vector<int>>& cameraDataVec) {
    return checkIntrusion_hw(sensorDataVec, cameraDataVec);
}

Event AnalysisModule::analyze(const vector<int>& sensorData, const vector<std::vector<int>>& cameraData) {
    if (checkIntrusion(sensorData, cameraData)) {
        return Trigger;
    }
    return NoEvent;
}
