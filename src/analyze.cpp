#include "..\\include\\alarm_system.h"
#include "..\\include\\analyze.h"
#include <chrono>
using namespace std::chrono;

void AnalysisModule::update(AlarmSystem& alarmSystem) {
    auto now = steady_clock::now();
    if (duration_cast<milliseconds>(now - lastSensorSample).count() >= 60) {
        sampleSensors();
        lastSensorSample = now;
    }
    if (duration_cast<milliseconds>(now - lastCameraSample).count() >= 120) {
        sampleCamera();
        lastCameraSample = now;
    }

    if (checkIntrusion()) {
        alarmSystem.handle_event(Event::Trigger);
    }
}