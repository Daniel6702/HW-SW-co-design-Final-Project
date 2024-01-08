#pragma once
#include <vector>
#include "analyze.h"
#include "input_controller.h"
#include "simulated_clock.h"

enum State {
    Inactive,
    Active,
    Alarmed
};

class AlarmSystem {
private:
    State current_state;
    AnalysisModule analysisModule;
    DataRetriever dataRetriever;
    uint64_t alarmTriggerTime;

    bool valid(int P) {
        return P % 2 == 0;
    }

    void reset() {
        handle_event(Reset);
    }

public:
    AlarmSystem() : current_state(Inactive) {}

    void update() {
        if (current_state == Active) {
            //Update sensor and camera data
            dataRetriever.update();

            //Retrieve and Analyze the data
            Event event = analysisModule.analyze(dataRetriever.getSensorData(), dataRetriever.getCameraData());

            //Handle the returned event 
            handle_event(event);
        } else if (current_state == Alarmed) {
            uint64_t now = SimulatedClock::now();
            if ((now - alarmTriggerTime) > 10000) {
                reset();
            }
        }
    }

    void manual_trigger() {
        vector<int> sensorData = {5, 5};
        vector<vector<int>> cameraData(9, vector<int>(9, 9));
        Event event = analysisModule.analyze(sensorData, cameraData);
        handle_event(event);
    }

    State getState() {
        return current_state;
    }

    void handle_event(Event event) {
        switch (current_state) {
            case Inactive:
                if (event == ValidCode) {
                    current_state = Active;
                }
                break;
            case Active:
                if (event == Trigger) {
                    current_state = Alarmed;
                    alarmTriggerTime = SimulatedClock::now();
                }
                break;
            case Alarmed:
                if (event == ValidCode) {
                    reset();
                } else if (event == Reset) {
                    current_state = Active;
                }
                break;
        }
    }

    bool enterPinCode(int code) {
        if (valid(code)) {
            handle_event(ValidCode);
            return true;
        } else {
            return false;
        }
    }
};
