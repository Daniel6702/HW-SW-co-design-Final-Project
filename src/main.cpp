#include <iostream>
#include "..\\include\\alarm_system.h"
#include "..\\include\\analyze.h"
using namespace std;

//g++ -o alarm_system main.cpp analyze.cpp

int main(void) {
    AlarmSystem alarmSystem;

    while (true) {
        alarmSystem.update();
    }

    return 0;
}