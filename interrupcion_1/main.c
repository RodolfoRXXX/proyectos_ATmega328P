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
uint8_t PUA = 0xff;

int main(void) {

    // desactiva las interrupciones globales
    cli();

    EICRA = (1 << ISC0) | (1 << ISC1);

}

// funciones
// función de configuración
void config_P() {
    DDRD = PD_entrada;
    DDRB = PD_salida;
    DDRC = PC_salida;
    PORTD = PUA;
    PORTB = 0x00;
    PORTC = 0x00;
}