/*
  Entrada para modificar registro D con un pulsador externo

  <<   >>
  w z W Z
*/

#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    // Seteo el puerto D, solo los bits 0 y 2 como entrada
    DDRD &= ~((1 << DDD0) & (1 << DDD2));

    // Configuro la resistencia pull-up interna del puerto 0 como desactivada
    PORTD &= ~(1 << PORTD0);
    
    // Configuro la resistencia pull-up interna del puerto 2 como activada
    PORTD |= (1 << PORTD2);

    while (1) {
        // El programa queda en bucle infinito.
        // Acá podrías leer PD0 o hacer otras tareas
    }

    return 0; // Opcional, pero buena práctica
}