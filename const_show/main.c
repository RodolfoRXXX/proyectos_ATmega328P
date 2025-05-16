/*
    Crear constantes A, B y C de 8 bits y mostrarlas en un array de leds
*/

#define F_CPU 1000000UL

#include <avr/io.h>

#include <utils/delay.h>

int main(void) {

    // Defino las constantes
    const uint8_t B = 0x96,
                  C = 76,
                  D = 0b00001111;

    DDRB = 0xff;
    DDRC = 0xff;
    DDRD = 0xff;

    PORTB = B;
    PORTC = C;
    PORTD = D;

    return 0
}