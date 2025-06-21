/*
    Declara los encabezados y funciones para el teclado matricial 4x4.
*/

#ifndef KEYPAD_H
#define KEYPAD_H

#include <stdint.h>

void init_port_keypad();
uint8_t scan_keypad();

#endif // KEYPAD_H
// Fin del archivo teclado_matricial_4x4/keypad.h