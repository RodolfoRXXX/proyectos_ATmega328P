/*
    Proyecto que empieza desde un binario con solo un 1 en el bit más significativo y realiza corrimiento hacia la izquierda cada cierto tiempo
*/

#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void) {

    DDRB = 0xff;
    PORTB = 0x00;

    uint8_t corrimiento = 0;

    while(1) {
        PORTB = (1 << corrimiento);
        corrimiento++;
        _delay_ms(500);
    }

}