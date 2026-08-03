#ifndef TIMER_H
#define TIMER_H

#include <chrono>

//Timer class to measure algorithm execution time.
class Timer
{
private:
    std::chrono::high_resolution_clock::time_point startTime;
    std::chrono::high_resolution_clock::time_point endTime;

public:
    void start();
    void stop();
    double getElapsedTime() const;
};

#endif