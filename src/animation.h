#ifndef ANIMATION_H_
#define ANIMATION_H_

#include "structs.h"

float animation_get_length(Timer* timer);
int current_frame(Animation* animation, Timer* timer);
void step_animation(Timer* timer, float delta_time);

#endif 
