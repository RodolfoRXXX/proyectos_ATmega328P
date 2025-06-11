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
#include <util/delay.h>

int ms = 0;
uint8_t time = 9;

// Array con la configuración de activado de cada led del display para multiplexado dinámico
const uint8_t display7seg[] = {
    0b00111111, // 0
    0b00000110, // 1
    0b01011011, // 2
    0b01001111, // 3
    0b01100110, // 4
    0b01101101, // 5
    0b01111101, // 6
    0b00000111, // 7
    0b01111111, // 8
    0b01101111  // 9
};

// prototipos

void config();
void mostrarDisplay(uint8_t valor);

// principal

int main(void) {

    // configuración
    config();
    sei();
    mostrarDisplay(time);

    while (1) {

        // si aprieta el botón D0, sube
        if (!(PIND & (1 << PIND0))) {
            _delay_ms(50);
            if (!(PIND & (1 << PIND0))) {
                if (time < 10) {
                    time++;
                    mostrarDisplay(time);
                }            
            }
            while (!(PIND & (1 << PIND0))); // esperar a que suelte el botón
        }

        // si aprieta el botón D1, baja
        if ((!(PIND & (1 << PIND1)))) {
            _delay_ms(50);
            if ((!(PIND & (1 << PIND1)))) {
                if (time > 1) {
                    time--;
                    mostrarDisplay(time);
                }            
            }
            while (!(PIND & (1 << PIND1))); // esperar a que suelte el botón
        }
    }
}

// Interrupción

ISR(TIMER0_COMPA_vect) {
    ms++;
    if (ms > time*10) {
        PORTB ^= (1 << PORTB0);
        ms = 0;
    }
}

// funciones

void config() {
    DDRB = (1 << DDB0);                                 // configura el PB0 como salida para el LED
    DDRD &= ~((1 << DDD0) | (1 << DDD1));               // configura dos pones D0 y D1 como entrada
    DDRC = 0xff;                                        // configuro el puerto C como salida
    PORTD &= (1 << PORTD1) | (1 << PORTD0);             // inhabilito las resistencias pull-up internas de los bits 0 y 1 del puerto D
    PORTC = 0x00;                                       // asigno el valor lógico 0 a todas las salidas del puerto C
    TCCR0A = (1 << WGM01);                              // configura el "Normal Mode" y CTC - clear time on compare match
    TCCR0B = (1 << CS02) | (0 << CS01) | (1 << CS00);   // configura el prescaler en 1024
    TIMSK0 = (1 << OCIE0A);                             // habilita la interrupción por comparación del registro A
    OCR0A = 19;
}

void mostrarDisplay(uint8_t valor) {
        if (valor <= 9) {
            PORTC = display7seg[valor];
        } else {
            PORTC = 0x00;
        }
}
