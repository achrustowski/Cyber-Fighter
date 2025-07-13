#ifndef TIMER_H_
#define TIMER_H_

#include <stdbool.h>
#include "structs.h"

Timer* initialize_timer(float length, float time, bool timeout);
void step_timer(Timer* timer, float delta_time);
bool is_timeout(Timer* timer);
float get_time(Timer* timer);
float get_length(Timer* timer);
void reset(Timer* timer);
void destroy_timer(Timer* timer);


#endif
