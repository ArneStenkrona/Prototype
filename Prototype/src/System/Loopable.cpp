#include "Loopable.h"
#include "math\lTimer.h"
#include "System\graphics\graphicsEngine.h"
void Loopable::start()
{
    setup();

    //The frames per second timer
    LTimer fpsTimer;
    //The frames per second cap timer
    LTimer capTimer;
    //Start counting frames per second
    fpsTimer.start();

    const size_t frameDurationSize = 100;
    int frameDurations[frameDurationSize];

    while (condition()) {
        capTimer.start();

        loop();
        //If frame finished early
        int frameTicks = capTimer.getMicroSeconds();
        if (frameTicks < GraphicsEngine::MICROSECONDS_PER_FRAME) {
            //Wait remaining time
            SDL_Delay((GraphicsEngine::MICROSECONDS_PER_FRAME - frameTicks) / 1000);
        }
        else {
            if (frameTicks > GraphicsEngine::MICROSECONDS_PER_FRAME + 1) {
                float fps = 1000000.f / frameTicks;
                printf(("FPS LOW: " + std::to_string(fps) + ". Expected: " + std::to_string(GraphicsEngine::SCREEN_FPS) + "\n").c_str());
            }

        }
        frameDurations[currentFrame % frameDurationSize] = frameTicks;
        if (currentFrame % frameDurationSize == 0) {
            double sum = 0;
            for (int i = 0; i < frameDurationSize; i++) {
                sum += frameDurations[i];
            }
            printf(("FPS: " + std::to_string(1000000.f / (sum / frameDurationSize)) + "\n").c_str());
        }
        currentFrame++;

        LWindow::updateAll();
    }
    cleanup();
}

void Loopable::setup()
{
}

void Loopable::cleanup()
{
}
