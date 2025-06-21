/*
    Configuración del proyecto
*/

#ifndef CONFIG_H
#define CONFIG_H

#include <avr/io.h>

// =================== Frecuencia del sistema ===================

#define F_CPU 1000000UL // Frecuencia del reloj del microcontrolador


// =================== Teclado 4x4 - Puerto y Pines ===================

#define KEYPAD_PORT   PORTD
#define KEYPAD_DDR    DDRD
#define KEYPAD_PIN    PIND

#define KEYPAD_ROW_MASK  0x0F  // PD0-PD3 como filas
#define KEYPAD_COL_MASK  0xF0  // PD4-PD7 como columnas

// =================== Display 7 segmentos - Puerto y Pines ===================

#define DISPLAY7SEG_PORT   PORTC
#define DISPLAY7SEG_DDR    DDRC
#define DISPLAY7SEG_PIN    PINC

#endif // CONFIG_H