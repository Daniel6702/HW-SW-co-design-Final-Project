#ifndef SIMULATED_CLOCK_H
#define SIMULATED_CLOCK_H

#include <cstdint>

class SimulatedClock {
private:
    static uint64_t currentTime;

public:
    // Initializes the simulated clock
    static void initialize() {
        currentTime = 0;
    }

    // Advances the simulated clock by the specified milliseconds
    static void advanceTime(uint64_t milliseconds) {
        currentTime += milliseconds;
    }

    // Gets the current time of the simulated clock
    static uint64_t now() {
        return currentTime;
    }
};

// Define the static variable
uint64_t SimulatedClock::currentTime = 0;

#endif // SIMULATED_CLOCK_H
