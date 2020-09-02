#include "Clock.hpp"
#include <SDL.h>

#define MILLIS SDL_GetTicks

namespace mode7
{

static int interval = 20;
static long cur = 0;
static long prev = 0;
static long elapsed = 0;
static long lag = 0;
static float ratio = 0.5f;

void Clock::start()
{
    prev = MILLIS();
    lag = 0;
}

void Clock::tick()
{
    cur = MILLIS();
    elapsed = cur - prev;
    prev = cur;
    lag += elapsed;
}

void Clock::lagTick()
{
    lag -= interval;
}

long Clock::delta()
{
    return elapsed;
}

bool Clock::lagging()
{
    return lag >= interval;
}

float Clock::extrapolate()
{
    float ex = (float)lag / (float)interval;
    if (ex < 0.0f || ex > 1.0f)
    {
        ex = 0.0f;
    }
    return ex;
}

};
