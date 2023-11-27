#include <iostream>
#include <windows.h>  
#include "..\\include\\alarm_system.h"
using namespace std;

int generatePinCode() {
    return rand() % 10;
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