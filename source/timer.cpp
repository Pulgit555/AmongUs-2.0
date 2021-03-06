#include "timer.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <GLFW/glfw3.h>

Timer::Timer(double interval) {
    prev = 0;
    this->interval = interval;
}

bool Timer::processTick() {
    double cur = glfwGetTime();
    if (cur - prev >= interval) {
        prev = cur;
        return true;
    } else
        return false;
}
