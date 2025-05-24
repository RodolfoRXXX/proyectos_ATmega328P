/*
    Proyecto que utiliza las interrupciones del microcontrolador, donde un array de leds se muestran en orden creciente y cuando se activa una
    interrupción, se activa un led que titila por 10 seg

    Las interrupciones son eventos que se disparan y activan alguna función determinada
    Hay dos tipoas, las interrupciones en los pines INT0 y INT1 que se encuentran en los pines digitales 2 y 3 respectivamente. Luego están los
    pines PCINT que son la gran mayoria de pines del micro, estos se separan en tres grupos y pueden ser activados por medio de un registro específico

    La activación y configuración de estado de estos pines de interrupción se manejan a través de registros EICRA y EIMSK

*/

#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

uint8_t PD_entrada = 0x00;
uint8_t PB_salida = 0xff;
uint8_t PC_salida = 0xff;
//uint8_t PUD = 0xff;

// prototipos
void config_P() {
    DDRD = PD_entrada;
    DDRB = PB_salida;
    DDRC = PC_salida;
    PORTD = 0xff;
    PORTB = 0x00;
    PORTC = 0x00;
}

int main(void) {

    uint8_t i;

    // Configuración
        config_P();

        // desactiva las interrupciones globales
        cli();

        // configuramos el modo en que se generan las interrupciones modificando el registro
        // INT0 se activa en flanco de bajada (ISC01 = 0, ISC00 = 1)
        EICRA = (1 << ISC00);

        // activar el pin INT0 o INT1 que va a estar pendiente de la interrupción
        // en este caso activamos el INT0
        EIMSK = (1 << INT0);

        // activamos las interrupciones globales
        sei();

    while (1) {
        for (i = 0; i < 255; i++) {
            PORTB = i;
            _delay_ms(500);
        }
        i = 0;
    }
}

// funciones
// función de interrupción
ISR(INT0_vect) {
    uint8_t i;
   for (i = 0; i < 10; i++) {
      PORTC ^= 0xFF;
      _delay_ms(500);
   }
   PORTC = 0x00; // Asegura que los LEDs estén apagados después
}

// función de configuración
