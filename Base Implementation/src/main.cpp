#include <iostream>
#include "..\\include\\alarm_system.h"
#include "..\\include\\simulated_clock.h" 
using namespace std;

unsigned generatePinCode() { 
    unsigned int lfsr = 0xACE1u;
    unsigned bit;
    bit  = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5) ) & 1;
    return (lfsr =  (lfsr >> 1) | (bit << 15)) % 10;
}

int main(void) {
    SimulatedClock::initialize();  
    AlarmSystem alarmSystem;

    while (true) {
        int pinCode = generatePinCode();
        if (alarmSystem.enterPinCode(pinCode) == true) {
            break;
        }
    }

    while (true) {
        alarmSystem.update();
        SimulatedClock::advanceTime(1);
    }
    return 0;
}
