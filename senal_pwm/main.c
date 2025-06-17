/*
  Programa que muestra como generar una señal PWM con un microcontrolador ATmega328P
  utilizando el temporizador 0 en modo Fast PWM. La frecuencia de la señal PWM es
  aproximadamente 976.5625 Hz y el ciclo de trabajo se puede ajustar entre 0% y 100%
  mediante la variable 'duty_cycle'. El pin de salida es el pin 6 (OC0A) del ATmega328P.
*/

#define F_CPU 1000000UL // Frecuencia del reloj del microcontrolador

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// Ciclo de trabajo inicial al 0%
    double duty_cycle = 0; // Valor entre 0 y 255

int main(void) {
    // Configurar el pin 6 (OC0A) como salida
    DDRD |= (1 << PD6);

    // Configurar el temporizador 0 en modo Fast PWM
    TCCR0A = (1 << WGM00) | (1 << WGM01) | (1 << COM0A1); // Modo Fast PWM, Clear OC0A on Compare Match
    TCCR0B = (1 << CS00) | (1 << CS02); // Prescaler 1024, sin prescaler
    TIMSK0 = (1 << TOIE0); // Habilitar interrupción por desbordamiento del temporizador 0


    sei(); // Habilitar interrupciones globales

    while (1) {
        
        // aumenta en 5 el dutycycle hasta llegar al 100% y cuando lo hace lo vuelve a poner en 0 con un delay de 25mseg(dimmer)

        _delay_ms(25); // Esperar 25 ms para simular el tiempo de parpadeo

        duty_cycle += 5; // Incrementar el ciclo de trabajo en 5

        if (duty_cycle > 255) {
            duty_cycle = 0; // Reiniciar al 0% después de llegar al 100%
        }
    }

    return 0;
}

// funciones de interrupción
ISR(TIMER0_OVF_vect) {
    // Aquí puedes manejar el desbordamiento del temporizador si es necesario
    OCR0A = (duty_cycle/100)*255; // Actualizar el ciclo de trabajo del PWM
}
