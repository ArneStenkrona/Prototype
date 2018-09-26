#include"timeMacros.h"

using namespace timeMacros;
std::chrono::time_point startTime = std::chrono::high_resolution_clock::now();
std::chrono::time_point finishTime = std::chrono::high_resolution_clock::now();

void timeMacros::start() {
    startTime = std::chrono::high_resolution_clock::now();
}
void timeMacros::stop() {
    finishTime = std::chrono::high_resolution_clock::now();
    auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(finishTime - startTime).count();
    std::cout << microseconds << " microseconds" << std::endl;
}