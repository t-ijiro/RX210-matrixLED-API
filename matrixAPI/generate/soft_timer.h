#ifndef SOFT_TIMER_H
#define SOFT_TIMER_H

#include "timer_event_t.h"

void soft_timer_init(void);

timer_event_t soft_timer_generate(void);

#endif /*SOFT_TIMER_H*/
