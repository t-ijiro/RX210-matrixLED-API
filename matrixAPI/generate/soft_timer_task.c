#include <stdint.h>
#include "soft_timer_task.h"
#include "Pencil.h"
#include "matrix.h"

// ************************************************************
// ダイナミック点灯処理
// ************************************************************
void timer_event_task_dynamic(void)
{
    uint16_t vert_data;
    static uint8_t vert_cnt = 0;

    vert_cnt = (vert_cnt + 1) % MATRIX_WIDTH;

    vert_data = matrix_get_data(vert_cnt);

    matrix_out(vert_cnt, vert_data);
}

// ************************************************************
// グラデーション処理
// ************************************************************
void timer_event_task_gradation(struct Pencil *pen, uint8_t num_pen, uint8_t num_color)
{
    uint8_t i;

    for(i = 0; i < num_pen; i++)
    {
        if(!pen[i].active)
        {
        	if(--pen[i].delay == 0)
			{
				pen[i].active = true;
			}

            continue;
        }

        if(matrix_read(pen[i].x, pen[i].y) != pixel_off)
        {
            matrix_write(pen[i].x, pen[i].y, pen[i].color);
        }

        pen[i].x = (pen[i].x + 1) % MATRIX_WIDTH;

    	if(pen[i].x == 0)
    	{
    		pen[i].y = (pen[i].y + 1) % MATRIX_HEIGHT;

    		if(pen[i].y == 0)
    		{
    			pen[i].color = 1 + pen[i].color % num_color;
    		}
    	}
    }

    // inherit = true
    matrix_present(true);
}

// ************************************************************
// スクロール処理
// ************************************************************
void timer_event_task_scroll(void)
{
    matrix_scroll_text('l');
}