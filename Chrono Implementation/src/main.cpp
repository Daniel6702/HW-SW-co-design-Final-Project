#include <iostream>
#include <windows.h>  
#include "..\\include\\alarm_system.h"
using namespace std;

unsigned generatePinCode() { 
    unsigned int lfsr = 0xACE1u;
    unsigned bit;
    bit  = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5) ) & 1;
    return (lfsr =  (lfsr >> 1) | (bit << 15)) % 10;
}

int main(void) {
    AlarmSystem alarmSystem;

    while (true) {
        int pinCode = generatePinCode();
        if (alarmSystem.enterPinCode(pinCode) == true) {
            break;
        }
    }

    while (true) {
        alarmSystem.update();
        Sleep(500);
    }
    
    return 0;
}

/*
Modularity and Single Responsibility Principle:
The system is broken down into distinct modules each with a clear responsibility. 
Likewise, each class encapsulates its data and behavior, adhering to the encapsulation principle.
The modular approach in the architecture is a key enabler for hardware-software co-design.
Each module can be independently evaluated for hardware acceleration based on their computational complexity.
The clear interfaces can be mapped to hardware-software communication protocols, such as AXI for FPGA-based designs.



*/