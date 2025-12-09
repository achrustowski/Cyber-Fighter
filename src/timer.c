#include "timer.h"

extern App app;

void step_timer(Timer* timer, float delta_time)
{
    timer->time += app.delta_time;
    if (timer->time >= timer->length)
    {
        timer->time -= timer->length;
        timer->timeout = true;
    }
}

bool is_timeout(Timer *timer)
{
    return timer->timeout;
}

float get_time(Timer *timer)
{
    return timer->time;
}

float get_length(Timer *timer)
{
    return timer->length;
}

void reset(Timer* timer)
{
    timer->time = 0;
}
