#pragma once
#include <vector>
#include "analyze.h"
#include "input_controller.h"
using namespace std::chrono;

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
    steady_clock::time_point alarmTriggerTime;

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
            dataRetriever.update();
            Event event = analysisModule.analyze(dataRetriever.getSensorData(), dataRetriever.getCameraData());
            handle_event(event);
        } else if (current_state == Alarmed) {
            auto now = steady_clock::now();
            if (duration_cast<seconds>(now - alarmTriggerTime).count() > 10) {
                reset();
            }
        }
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
                    alarmTriggerTime = std::chrono::steady_clock::now();
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
