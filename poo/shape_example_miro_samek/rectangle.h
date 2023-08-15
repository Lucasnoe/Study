#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

typedef struct {
    //classe herdada
    Shape super; //para que Rectangle sejaconsiderada uma subclasse de Shape é necessário que o primeiro membro da estrutura seja uma instância da classe Shape.

    // atributos específicos da classe
    uint16_t width;
    uint16_t height;
} Rectangle;


void Rectangle_ctor(Rectangle * const me, int16_t x0, int16_t y0, uint16_t w0, uint16_t h0); // "me" é um ponteiro constante que aponta para um dado do tipo Shape que pode ser modificado

// void Rectangle_draw(const Rectangle * const me, int16_t dx, int16_t dy);

uint16_t Rectangle_area(const Rectangle * const me);

uint16_t Rectangle_perimeter(const Rectangle * const me);

#endif