#pragma once
#include <stdint.h>

class LTimer
{
public:
    //Initializes variables
    LTimer();

    //The various clock actions
    void start();
    void stop();
    void pause();
    void unpause();

    //Gets the timer's time
    long getMicroSeconds();

    //Checks the status of the timer
    bool isStarted();
    bool isPaused();

private:
    //The clock time when the timer started
    uint64_t mStartTicks;

    //The ticks stored when the timer was paused
    uint64_t mPausedTicks;

    //The timer status
    bool mPaused;
    bool mStarted;
};