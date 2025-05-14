/*
    Programa Hola Mundo en Bare Metal
    Enciende y apaga un led a través del pin PB0 y utilizando funciones de la libreria avr/io.h
*/

#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>


int main(void) {
    
    // seteo el registro Data Direction Register B como entrada o salida, en este caso como salida = el bit 0 y el bit 3
    // el primero miembro indica que al 1 decimal(0b00000001) se le hace un corrimiento hacia la izquierda de 0 unidades, ya que DB0 = 0
    // el segundo miembro indica que al 1 decimal(0b00000001) se le hace un corrimiento hacia la izquierda de 2 unidades, ya que DB2 = 2
    // DDRB = DDRB | 0b00000001 | 0b00000100
    //     0b00000000
    // OR  0b00000001
    // OR  0b00000100
    // =   0b00000101
    DDRB |= (1 << DDB0) | (1 << DDB2);

    while (1)
    {
        // ENCENDER PB0
        //     0b00000000
        // OR  0b00000001
        // =   0b00000001
        PORTB |= (1 << PORTB0);

        // APAGAR PB2
        //     0b00000001
        // AND 0b11111011
        // =   0b00000001
        PORTB &= ~(1 << PORTB2);
        _delay_ms(1000);

        // APAGAR PB0
        //     0b00000001
        // AND 0b11111110
        // =   0b00000000
        PORTB &= ~(1 << PORTB0);

        // ENCENDER PB2
        //     0b00000000
        // OR  0b00000100
        // =   0b00000100
        PORTB |= (1 << PORTB2);
        _delay_ms(1000);

    }
}
