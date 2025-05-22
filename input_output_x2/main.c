/*
    Proyecto que toma la entrada del puerto D en binario y responde desde el puerto C encendiendo dos displays de 8 segmentos
    mostrando dígitos en decimal hasta 99
*/

#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>

const uint8_t numeros7seg[] = {
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

void config_P() {
    DDRD = 0x00;   // PIND como entrada
    DDRC = 0xFF;   // PORTC como salida (segmentos A-G)
    DDRB = 0xFF;   // PORTB como salida (control de displays)
    PORTD = 0xFF;  // Pull-ups en entrada
    PORTC = 0x00;  // Apagar segmentos al inicio
    PORTB |= (1 << PORTB0) | (1 << PORTB1) | (1 << PORTB2);  // Todos los displays desactivados al inicio (activo en bajo)
}

int main(void) {
    config_P();

    while (1) {
        uint8_t valor = PIND;
        //if (valor > 99) valor = 99;  // Limitar máximo

        uint8_t unidades = valor % 10;
        uint8_t decenas = (valor / 10) % 10;
        uint8_t centenas = valor / 100;

        // Mostrar centenas
        PORTC = numeros7seg[centenas];
        PORTB |= (1 << PORTB0) | (1 << PORTB1) | (1 << PORTB2);
        PORTB &= ~(1 << PORTB0);  // Activar display centenas
        _delay_ms(1);

        // Mostrar decenas
        PORTC = numeros7seg[decenas];
        PORTB |= (1 << PORTB0) | (1 << PORTB1) | (1 << PORTB2);
        PORTB &= ~(1 << PORTB1);  // Activar display decenas
        _delay_ms(1);

        // Mostrar unidades
        PORTC = numeros7seg[unidades];
        PORTB |= (1 << PORTB0) | (1 << PORTB1) | (1 << PORTB2);
        PORTB &= ~(1 << PORTB2);  // Activar display decenas
        _delay_ms(1);

    }
}
