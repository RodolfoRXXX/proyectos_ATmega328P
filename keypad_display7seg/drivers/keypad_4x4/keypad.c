/*
    Teclado matricial 4x4

    PUERTO D

    Este archivo contiene el código para leer un teclado matricial 4x4 utilizando un microcontrolador AVR.
    Las filas están conectadas a PD0 a PD3 y las columnas a PD4 a PD7.
    El código configura las filas como salidas y las columnas como entradas con resistencias pull-up.
    Luego, escanea el teclado activando cada fila y leyendo las columnas para detectar
    qué teclas están presionadas. Si una columna está en bajo, se considera que
    la tecla correspondiente está presionada. El código puede ser modificado para realizar
    acciones específicas cuando se detecta una tecla presionada, como imprimir el valor de la tecla

    Este código es parte de una libreria que controla el teclado matricial 4x4.

    1  2  3  A
    4  5  6  B
    7  8  9  C
    E  0  F  D
*/

#include "../../config/config.h"
#include <avr/io.h>
#include <util/delay.h>

#include "keypad.h"

static const uint8_t keypad_map[4][4] = {
    {0x1, 0x2, 0x3, 0xA},
    {0x4, 0x5, 0x6, 0xB},
    {0x7, 0x8, 0x9, 0xC},
    {0xE, 0x0, 0xF, 0xD}
};

void init_port_keypad() {
    // Configurar filas como salidas
    KEYPAD_DDR |= KEYPAD_ROW_MASK; // PD0 a PD3 como salidas(0000 1111)
    // Configurar columnas como entradas con pull-up
    KEYPAD_DDR &= ~KEYPAD_COL_MASK; // PD4 a PD7 como entradas((0000 1111)&(0000 1111) = 0000 1111)
    KEYPAD_PORT |= (KEYPAD_ROW_MASK | KEYPAD_COL_MASK); // Habilitar pull-up en PD4 a PD7 y asigna PD0 a PD3 en alta
}

uint8_t scan_keypad() {
    uint8_t row;
    uint8_t col;
    for (row = 0; row < 4; row++) {
        // Activar fila
        KEYPAD_PORT &= ~(1 << row); // Poner fila en bajo
        _delay_ms(5); // Esperar estabilización

        // Leer columnas
        uint8_t cols = KEYPAD_PIN & KEYPAD_COL_MASK; // Leer PD4 a PD7

        if (cols != KEYPAD_COL_MASK) { // Si alguna columna está en bajo
            for (col = 0; col < 4; col++) {
                if (!(cols & (1 << (col + 4)))) { // Verificar si la columna está en bajo
                    while (!(KEYPAD_PIN & (1 << (col + 4)))); // Esperar a que la tecla se mantenga presionada
                    return keypad_map[row][col]; // Retornar el valor de la tecla presionada
                }
            }
        }

        // Desactivar fila
        KEYPAD_PORT |= (1 << row); // Poner fila en alto
    }
    return 0xFF; // Retornar 0xFF si no se presionó ninguna tecla
}