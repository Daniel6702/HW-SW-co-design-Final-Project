#pragma once
#include <vector>
#include "analyze.h"
#include "input.h"

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

    public:
        AlarmSystem() {
            current_state = Active;
            analysisModule.signal.connect([this](Event e) {handle_event(e);});
            dataRetriever.sensorSignal.connect([this](std::vector<int> data) {analysisModule.processSensorData(data);});
            dataRetriever.cameraSignal.connect([this](std::vector<std::vector<int>> data) {analysisModule.processCameraData(data);});
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
                dataRetriever.update();
                analysisModule.update();
            }
        }
};