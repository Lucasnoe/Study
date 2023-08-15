#include <stdio.h>
#include "rectangle.h"
#include <stdint.h>

Rectangle rec;



uint16_t area;
uint16_t perimeter;

int main(void)
{
    Rectangle_ctor(&rec, 0, 0, 4, 5);

    perimeter = Rectangle_perimeter(&rec);
    area = Rectangle_area(&rec);
    printf("The initial position of the rectangle is(%d,%d)\n", rec.super.x, rec.super.y); // Uma subclasse pode utilizar funções da classe herdada, mas é necerssário fazer um casting explícito
    Shape_moveBy((Shape *)&rec, 1, 1);
    printf("The new position of the rectangle is(%d,%d)\n", rec.super.x, rec.super.y);

    printf("the calculed area is: %d \n", area);
    printf("the calculed perimter is: %d \n", perimeter);

    return 0;
}