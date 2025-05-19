/*
    Configurar el PORTB como salida y setearlo en 255, luego de 3 segundos limpiar con XOR, 3 segundos despues, encender los bits:
    0, 1, 3, 5, 6 y 3 segundos más tarde seleccionar nibble alto con AND en PORTB
*/

#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void) {

    DDRB = 0xff;
    PORTB = 0x00;
    uint8_t B = 255;

    while(1) {
        // Setear el PORTB = 255 y esperar 3 segundos
        PORTB = B;
        _delay_ms(3000);

        // Limpiar el registro con XOR
        PORTB ^= PORTB;
        _delay_ms(3000);

        // Encender los bits: 0, 1, 3, 5, 6
        PORTB |= (1 << 0) | (1 << 1) | (1 << 3) | (1 << 5) | (1 << 6);
        _delay_ms(3000);

        // Seleccionar nibble alto con AND
        PORTB &= 0b11110000;
        _delay_ms(3000);

    }

}