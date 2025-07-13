#include "timer.h"
#include <stdlib.h>
#include <string.h>

extern App app;

Timer* initialize_timer(float length, float time, bool timeout)
{
    Timer* timer = (Timer*)malloc(sizeof(Timer));
    timer->length = length;
    timer->time = time;
    timer->timeout = timeout;

    return timer;
}

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

void destroy_timer(Timer *timer)
{
    memset(timer, 0, sizeof(Timer));
    free(timer);
}
