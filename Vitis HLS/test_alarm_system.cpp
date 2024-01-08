#include <cassert>
#include <iostream>
#include "..\\include\\alarm_system.h"
#include "..\\include\\simulated_clock.h"

using namespace std;

//g++ -o test_alarm_system.exe test_alarm_system.cpp analyze.cpp
//g++ -pg -o program test_alarm_system.cpp analyze.cpp     
//g++ -g test_alarm_system.cpp analyze.cpp -o program

void testAlarmSystem() {
    SimulatedClock::initialize();

    AlarmSystem alarmSystem;

    assert(!alarmSystem.enterPinCode(1)); 

    assert(alarmSystem.getState() == Inactive);

    assert(alarmSystem.enterPinCode(2));

    assert(alarmSystem.getState() == Active);

    for (int i = 0; i < 100000000; ++i) {
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
