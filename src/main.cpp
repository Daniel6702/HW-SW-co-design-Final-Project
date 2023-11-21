#include <iostream>
#include <windows.h>  
#include "..\\include\\alarm_system.h"
using namespace std;

int main(void) {
    AlarmSystem alarmSystem;

    while (true) {
        alarmSystem.update();
        Sleep(500);
    }

    return 0;
}
