/*
    Declara los encabezados y funciones para el display de 7 segmentos.
*/

#ifndef DISPLAY7SEG_H
#define DISPLAY7SEG_H

#include <stdint.h>

void init_ports_display7seg();
void display_digit(uint8_t digit);

#endif // DISPLAY7SEG_H
// Fin del archivo display_7seg/display7seg.h