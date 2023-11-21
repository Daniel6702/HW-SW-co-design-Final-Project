#ifndef SIGNAL_H  
#define SIGNAL_H 

#include <functional>
#include <vector>
#include "events.h"

template<typename... Args>
class Signal {
public:
    using Slot = std::function<void(Args...)>;

    void connect(const Slot& slot) {
        slots.push_back(slot);
    }

    void emit(Args... args) {
        for (auto& slot : slots) {
            slot(args...);
        }
    }

private:
    std::vector<Slot> slots;
};

#endif 