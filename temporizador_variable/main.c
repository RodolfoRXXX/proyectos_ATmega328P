/*
    Temporizador que modifica el tiempo de parpadeo de un LED con dos botones
        Un botón para aumentar la frecuencia del parpadeo y otro para disminuirlo

        Programa que tiene dos botones en los puertos D0 y D1, como botón de subida y de bajada respectivamente
        y un LED en el puerto B0
        al apretar cada uno de estos botones alteramos el tiempo de parpadeo aumentando o disminuyendo su frecuencia.
        Mantenemos como base el tiempo de 200mseg, pero con los pulsadores varíamos la cantidad necesaria de interrupciones
        que se necesitan para ingresar al bucle if y modificar el valor del bit de salida del LED para generar el parpadeo.
*/

#define F_CPU 1000000UL

#include <avr/io.h>
#include <avr/interrupt.h>

int ms = 0;
int time = 5;

// prototipos

void config();


// principal

int main(void) {

    // configuración
    config();

    sei();

    while (1) {

        // si aprieta el botón D0, sube
        if (!(PIND & (1 << PIND0)) && (time < 11)) {
            time++;
        }

        // si aprieta el botón D1, baja
        if((!(PIND & (1 << PIND1))) && (time > 1)) {
            time--;
        }
    }
}

// funciones

void config() {
    DDRB = (1 << DDB0);         // configura el PB0 como salida para el LED
    DDRD = (0 << DDD1) | (0 << DDD0);    // configura dos pones D0 y D1 como entrada
    PORTD = (0 << DDD1) | (0 << DDD0);   // inhabilito las resistencias pull-up internas de los bits 0 y 1 del puerto D
    TCCR0A = (1 << WGM01);      // configura el "Normal Mode" y CTC - clear time on compare match
    TCCR0B = (1 << CS02) | (0 << CS01) | (1 << CS00);  // configura el prescaler en 1024
    TIMSK0 = (1 << OCIE0A);     // habilita la interrupción por comparación del registro A
    OCR0A = 195.31;
}

ISR(TIMER0_COMPA_vect) {
    ms++;
    if (ms > time) {
        PORTB ^= (1 << PORTB0);
        ms = 0;
    }
}