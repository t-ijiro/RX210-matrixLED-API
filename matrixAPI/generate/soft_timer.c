#include <stdint.h>
#include "soft_timer.h"
#include "timer_event_t.h"
#include "period.h"

static uint32_t counter_dynamic;
static uint32_t counter_gradation;
static uint32_t counter_scroll;

void soft_timer_init(void)
{
	counter_dynamic   = PERIOD_DYNAMIC_MS;
	counter_gradation = PERIOD_GRADATION_MS;
	counter_scroll    = PERIOD_SCROLL_MS;
}

timer_event_t soft_timer_generate(void)
{
	timer_event_t ev = TASK_NONE;

	if(--counter_dynamic == 0)
	{
		ev |= TASK_DYNAMIC;
		counter_dynamic = PERIOD_DYNAMIC_MS;
	}

	if(--counter_gradation == 0)
	{
		ev |= TASK_GRADATION;
		counter_gradation = PERIOD_GRADATION_MS;
	}

	if(--counter_scroll == 0)
	{
		ev |= TASK_SCROLL;
		counter_scroll = PERIOD_SCROLL_MS;
	}

	return ev;
}
