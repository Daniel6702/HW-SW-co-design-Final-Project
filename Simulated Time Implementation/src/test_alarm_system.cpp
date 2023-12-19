#include <cassert>
#include <iostream>
#include "..\\include\\alarm_system.h"
#include "..\\include\\simulated_clock.h"

using namespace std;

void testAlarmSystem() {
    SimulatedClock::initialize();

    AlarmSystem alarmSystem;

    assert(alarmSystem.getState() == Inactive);

    assert(!alarmSystem.enterPinCode(1)); 

    assert(alarmSystem.enterPinCode(2));

    assert(alarmSystem.getState() == Active);

    for (int i = 0; i < 1000; ++i) {
        alarmSystem.update();
        SimulatedClock::advanceTime(10);
    }

    assert(alarmSystem.getState() == Active || alarmSystem.getState() == Alarmed);
    
    alarmSystem.manual_trigger();

    assert(alarmSystem.getState() == Alarmed);

    cout << "All tests passed successfully." << endl;
}

int main() {
    testAlarmSystem();
    return 0;
}
