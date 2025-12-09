#ifndef TIMER_H_
#define TIMER_H_

#include <stdbool.h>
#include "structs.h"

void step_timer(Timer* timer, float delta_time);
bool is_timeout(Timer* timer);
float get_time(Timer* timer);
float get_length(Timer* timer);
void reset(Timer* timer);

#endif
