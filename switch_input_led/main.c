/*
  Entrada para modificar registro D con un pulsador externo y encender un led

  <<   >>
  w z W Z
*/

#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    // Seteo el puerto D, solo los bits 0 y 2 como entrada
    DDRD &= ~((1 << DDD0) | (1 << DDD2));

    // Seteo el puerto B, solos los pines 0 y 2 que tienen como salida leds
    DDRB |= (1 << DDB0) | (1 << DDB2);

    // Configuro la resistencia pull-up interna del puerto 0 como desactivada
    PORTD &= ~(1 << PORTD0);
    
    // Configuro la resistencia pull-up interna del puerto 2 como activada
    PORTD |= (1 << PORTD2);

    // Configurar los valores por defecto del puerto B, ambos bits con salida 0
    PORTB &= ~((1 << PORTB0) | (1 << PORTB2));

    while (1) {
        // Leo el valor del puerto D
        /*
        if (!(PIND & (1 << PIND0))) {
            PORTB |= (1 << PORTB0);
        } else {
            PORTB &= ~(1 << PORTB0);
        }
        if (!(PIND & (1 << PIND2))) {
            PORTB |= (1 << PORTB2);
        } else {
            PORTB &= ~(1 << PORTB2);
        }
            */

        while (!(PIND & (1 << PIND0))) {
            // prende led
            PORTB |= (1 << PORTB0);
            _delay_ms(500);

            // apaga led
            PORTB &= ~(1 << PORTB0);
            _delay_ms(500);
        }

        while (!(PIND & (1 << PIND2))) {
            // prende led
            PORTB |= (1 << PORTB2);
            _delay_ms(500);

            // apaga led
            PORTB &= ~(1 << PORTB2);
            _delay_ms(500);
        }
        
    }

    return 0; // Opcional, pero buena práctica
}