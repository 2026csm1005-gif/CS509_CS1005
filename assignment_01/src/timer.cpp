#include "../include/timer.h"

using namespace std::chrono;

//Starts the timer.
void Timer::start()
{
    startTime = high_resolution_clock::now();
}

//Stops the timer.
void Timer::stop()
{
    endTime = high_resolution_clock::now();
}

//Returns elapsed time in milliseconds.
double Timer::getElapsedTime() const
{
    return duration<double, std::milli>(endTime - startTime).count();
}