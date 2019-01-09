#pragma once
#include "System\GUI\Window\lwindow.h"

//Base class for runnable loops, like the editor or gameLogic
class Loopable {
public:
    //Runs the loop
    //If window is closed, the loop exits
    void start();
protected:
    //Loop to be implemented by subclass
    //Set up may be done here
    virtual void setup();
    //Main loop may be done here
    virtual void loop() = 0;
    //Cleanup may be done here
    virtual void cleanup();
    //Condition for loop to run
    virtual bool condition() = 0;
private:
    //Current frame of the loop
    static long currentFrame;
};