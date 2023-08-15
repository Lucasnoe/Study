#ifndef SHAPE_H
#define SHAPE_H

#include <stdint.h>

// Implementação da classe "Shape"

typedef struct {
    int16_t x;
    int16_t y;
} Shape;            

// Constructor serve para inicializar um objeto da classe "Shape"

void Shape_ctor(Shape * const me, int16_t x0, int16_t y0);  // "me" é um ponteiro constante que aponta para um dado do tipo Shape que pode ser modificado

void Shape_moveBy(Shape * const me, int16_t dx, int16_t dy);

uint16_t Shape_distanceFrom(const Shape * const me, Shape const * other);


#endif