/*
    Programa que implementa un segundero utilizando el timer del microcontrolador ATmega328P
        Este segundero detalla el funcionamiento del timer del micro, configurando los registros
        destinados a ello.

        El segundero se realiza utilizando el registro de comparación A del timer 0 para generar
        una interrupción por comparación y devolver el timer a 0, el tiempo que se tarda en realizar
        esta interrupción se calcula en base a la frecuencia de trabajo configurada del micro
        y al período de tiempo que se desea que se genere la interrupción.asm
        Este timer se utiliza para hacer funcionar un LED de forma intermitente, durante cada período
        de tiempo elegido.

        Cálculo del tick

        Fosc = 1000000 hz
        Vpres = 1024
        Fpres = 1000000/1024 = 976.56 hz
        tick = 1/Fpres = 0.001024seg = 1.024mseg

        Tmax del timer = 0.001024 * 255 = 0.26seg

        OCR = T / tick    // el OCR es el tiempo total dividido el valor de tiempo de cada tick, 
                          // es decir, el tiempo que debe transcurrir en el timer para que al comparar
                          // se produzca la interrupción

        OCR = T * Fpres = 976.56 // como es mucho mayor a 255, que es el límite de ticks, entonces usamos una base de tiempo más chica

        T = 0.2seg = 200mseg  // se necesitan 5 interrupciones para llegar al segundo

        OCR = 0.2seg * 976.56hz = 195.31 ok

*/

#define F_CPU 1000000UL

#include <avr/io.h>
#include <avr/interrupt.h>

int ms = 0;

int main(void) {

    // configuración
    DDRB = (1 << DDB0);         // configura el PB0 como salida para el LED
    TCCR0A = (1 << WGM01);      // configura el "Normal Mode" y CTC - clear time on compare match
    TCCR0B = (1 << CS02) | (0 << CS01) | (1 << CS00);  // configura el prescaler en 1024
    TIMSK0 = (1 << OCIE0A);     // hbilita la interrupción por comparación del registro A
    OCR0A = 195.31;

    sei();

    while (1) {
        /* code */
    }

}

ISR(TIMER0_COMPA_vect) {
    ms++;  // en cada interrupción aumenta el contador
    if(ms > 5) {  // si se llegan a 5 interrupciones entra al bucle
        PORTB ^= (1 << PORTB0);  // parpadea el LED
        ms = 0;                  // reinicia el contador
    }
}
