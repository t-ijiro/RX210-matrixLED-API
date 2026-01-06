#ifndef PENCIL_H
#define PENCIL_H

#include <stdint.h>
#include <stdbool.h>
#include "matrix.h"

struct Pencil{
	uint8_t x;
	uint8_t y;
	pixel_color_t color;
    uint8_t delay;
	bool active;
};

#endif /*PENCIL_H*/