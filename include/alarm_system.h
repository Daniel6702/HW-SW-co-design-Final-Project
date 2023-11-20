#pragma once
#include <vector>
#include "analyze.h"

enum State {
    Inactive,
    Active,
    Alarmed
};

class AlarmSystem {
    private:
        State current_state;
        AnalysisModule analysisModule;

    public:
        AlarmSystem() {
            current_state = Inactive;
        }

        void handle_event(Event e) {
            switch (current_state) {
                if (e == Trigger) {
                    current_state = Alarmed;
                }
            }
        }

        void update() {
            if (current_state == Active) {
                analysisModule.update(*this);
            }
        }
};