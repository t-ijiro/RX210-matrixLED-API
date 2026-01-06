//#include "typedefine.h"
#ifdef __cplusplus
//#include <ios>                        // Remove the comment when you use ios
//_SINT ios_base::Init::init_cnt;       // Remove the comment when you use ios
#endif

#include <stdint.h>
#include <stdbool.h>
#include <machine.h>
#include "iodefine.h"
#include "hardwareInit.h"
#include "soft_timer.h"
#include "soft_timer_task.h"
#include "timer_event_t.h"
#include "Pencil.h"
#include "period.h"
#include "matrix.h"

#define NUM_PENCIL 3
#define NUM_COLOR  3

volatile bool timer_interrupt_flag_1ms = false;

void main(void);
#ifdef __cplusplus
extern "C" {
void abort(void);
}
#endif

void main(void)
{
	timer_event_t timer_event_flag = TASK_NONE;

	struct Pencil pen[NUM_PENCIL] =
	{
		{0, 0, pixel_red,    1,  false},
		{0, 0, pixel_green,  32, false},
		{0, 0, pixel_orange, 64, false}
	};

	init_CLK();
	init_CMT0(1u);  // 1ms周期
	matrix_init();
	soft_timer_init();

	matrix_set_scroll_text("HELLO WORLD");
	matrix_set_scroll_colors(pixel_red, pixel_off);

	while(1)
	{
		if(timer_interrupt_flag_1ms)
		{
			timer_event_flag = soft_timer_generate();

			timer_interrupt_flag_1ms = false;
		}

		if(timer_event_flag & TASK_DYNAMIC)
		{
			timer_event_task_dynamic();

			timer_event_flag &= ~TASK_DYNAMIC;
		}

		if(timer_event_flag & TASK_GRADATION)
		{
			timer_event_task_gradation(pen, NUM_PENCIL, NUM_COLOR);

			timer_event_flag &= ~TASK_GRADATION;
		}

		if(timer_event_flag & TASK_SCROLL)
		{
			timer_event_task_scroll();

			timer_event_flag &= ~TASK_SCROLL;
		}
	}
}

#ifdef __cplusplus
void abort(void)
{

}
#endif


