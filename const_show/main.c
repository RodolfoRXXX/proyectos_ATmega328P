/*
    Crear constantes A, B y C de 8 bits y mostrarlas en un array de leds
*/

#define F_CPU 1000000UL

#include <avr/io.h>

#include <util/delay.h>

int main(void) {

    // Defino las constantes B en hexadecimal, C en decimal y D en binario
    const uint8_t B = 0x96,
                  C = 76,
                  D = 0b00001111;

    // Seteo los registros de dirección como salidas (0b11111111)
    DDRB = 0xff;
    DDRC = 0xff;
    DDRD = 0xff;

    // Seteo los puertos con las constantes
    PORTB = B/3;
    PORTC = C*3;
    PORTD = C%D;

    return 0;
}