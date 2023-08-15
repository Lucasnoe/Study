#include "rectangle.h"

void Rectangle_ctor(Rectangle * const me, int16_t x0, int16_t y0, uint16_t w0, uint16_t h0)
{
    Shape_ctor(&me->super, x0, y0);
    me->height = h0;
    me->width = w0;
}

// void Rectangle_draw(const Rectangle * const me, int16_t dx, int16_t dy);

uint16_t Rectangle_area(const Rectangle * const me)
{
    return(me->height * me->width);
}

uint16_t Rectangle_perimeter(const Rectangle * const me)
{
    return(2*me->height + 2*me->width);
}