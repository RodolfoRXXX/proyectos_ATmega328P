/*
    Projecto que incrementa desde 0 hasta 255 y muestra ese número en binario
*/

#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>


int main(void) {
    DDRB = 0xff;
    PORTB = 0x00;

    uint8_t incremento = 0;

    while (1)
    {
        while(incremento < 255) {
        PORTB = incremento;
        incremento++;
        _delay_ms(30);
        }
        while(incremento > 0) {
            PORTB = incremento;
            incremento--;
            _delay_ms(30);
        }
    }
}