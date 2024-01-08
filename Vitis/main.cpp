#include "..\\include\\alarm_system.h"
#include "..\\include\\simulated_clock.h" 
#include "..\\include\\gpio.h" 

int main(void) {
    initiate_gpio();

    bool state = false;

    SimulatedClock::initialize();  
    AlarmSystem alarmSystem;

    TurnOnLed(LED1);

    while(true) {
        if (IsButtonPressed(BUTTON1) == true) {
            alarmSystem.enterPinCode(VALID_PINCODE);
            TurnOffLed(LED1 | LED3);
        } else if (IsButtonPressed(BUTTON2) == true && alarmSystem.getState() == Active) {
            alarmSystem.manual_trigger();
            TurnOffLed(LED2);            
        }

        if (SimulatedClock::now() % 100000 == 0) {
            InvertLedState(LED2);
        } 

        if (alarmSystem.getState() == Alarmed) {
            TurnOnLed(LED3);
        }

        alarmSystem.update();
        SimulatedClock::advanceTime(1);
    }
}