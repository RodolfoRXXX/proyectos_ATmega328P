/*
    Programa Hola Mundo en Bare Metal
    Enciende y apaga un led a través del pin PB0 y utilizando funciones de la libreria avr/io.h
*/

#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>


int main(void) {
    
    // seteo el registro Data Direction Register B como entrada o salida, en este caso como salida = el bit 0 y el bit 3  
    DDRB |= (1 << DDB0) | (1 << DDB2);

    while (1)
    {
        // Coloco el bit 0 y el bit 2 del registro B en 1 binario para encenderlo
        PORTB |= (1 << PORTB0);
        PORTB &= ~(1 << PORTB2);
        _delay_ms(1000);

        // Coloco el bit 0 en 0 binario para apagarlo
        PORTB &= ~(1 << PORTB0);
        PORTB |= (1 << PORTB2);
        _delay_ms(1000);

    }
}

