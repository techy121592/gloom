#include "Timer.h"
#include <SDL.h>

long Clock1;

long TimeElapsed()
{
    long timeDif=SDL_GetTicks() - Clock1;
    return timeDif;
}

void TimerStart()
{
    Clock1 = SDL_GetTicks();
}
