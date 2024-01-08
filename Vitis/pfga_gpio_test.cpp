#include "xil_io.h"

#define LED_BASE_ADDR 0x40020000
#define BTN_BASE_ADDR 0x40010000
#define GPIO_DATA_OFFSET 0x0000
#define GPIO_DIR_OFFSET 0x0004

#define VALID_PINCODE 2

#define LED1 (1 << 0) 
#define LED2 (1 << 1) 
#define LED3 (1 << 2) 
#define LED4 (1 << 3) 

#define BUTTON1 (1 << 0) 
#define BUTTON2 (1 << 1) 
#define BUTTON3 (1 << 2) 
#define BUTTON4 (1 << 3) 

void WriteGpio(u32 BaseAddress, int Offset, u32 Data) {
    Xil_Out32(BaseAddress + Offset, Data);
}

u32 ReadGpio(u32 BaseAddress, int Offset) {
    return Xil_In32(BaseAddress + Offset);
}

void TurnOnLed(u32 led) {
    u32 current = ReadGpio(LED_BASE_ADDR, GPIO_DATA_OFFSET);
    WriteGpio(LED_BASE_ADDR, GPIO_DATA_OFFSET, current | led);
}

void TurnOffLed(u32 led) {
    u32 current = ReadGpio(LED_BASE_ADDR, GPIO_DATA_OFFSET);
    WriteGpio(LED_BASE_ADDR, GPIO_DATA_OFFSET, current & ~led);
}

bool IsButtonPressed(u32 button) {
    u32 current = ReadGpio(BTN_BASE_ADDR, GPIO_DATA_OFFSET);
    return (current & button) != 0;
}

void wait(int time) {
    for(volatile int i = 0; i < time; i++) {}
}

void initiate_gpio() {
    WriteGpio(BTN_BASE_ADDR, GPIO_DIR_OFFSET, 0xFFFFFFFF);
    WriteGpio(LED_BASE_ADDR, GPIO_DIR_OFFSET, 0x0);
}

int main(void) {
    initiate_gpio();

    while(IsButtonPressed(BUTTON1) == false) {}

    while(true) {
        TurnOnLed(LED2 | LED3);
        wait(10000000);
        TurnOffLed(LED2 | LED3);
        wait(10000000);
    }
}
