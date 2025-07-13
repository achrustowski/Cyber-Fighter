#include "animation.h"
#include "timer.h"
#include "structs.h"

Animation initialize_animation(Timer* timer, int frame_count, float length)
{
    Animation animation;
    animation.frame_count = frame_count;
    timer->length = length;

    return animation;
}

float animation_get_length(Timer* timer)
{
    return timer->length;
}

int current_frame(Animation* animation, Timer* timer)
{
    return (int)(get_time(timer) / get_length(timer) * animation->frame_count);
}

void step_animation(Timer* timer, float delta_time)
{
    step_timer(timer, delta_time);
}
