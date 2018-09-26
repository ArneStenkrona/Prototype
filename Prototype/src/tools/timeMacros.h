#pragma once
#include <chrono>
#include <iostream>
#define MEASURETIME(x) timeMacros::start();\
    x;\
    timeMacros::stop()
    

namespace timeMacros {
    void start();
    void stop();
}
