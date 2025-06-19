/*
    Controlador para un display de 7 segmentos

    PUERTO C

    Este archivo contiene el código para controlar un display de 7 segmentos utilizando un microcontrolador AVR.
    El display está conectado a los pines del puerto C del microcontrolador.
    El código define una función para mostrar un dígito del 0 al 9 y de A hasta F en el display de 7 segmentos.
    El mapa de segmentos se define en un arreglo, donde cada elemento representa el estado de los
    segmentos del display para cada dígito. Los segmentos se activan al poner el pin correspondiente en alto.
    El código puede ser modificado para mostrar diferentes dígitos o caracteres en el display de 7 segmentos.
    El display de 7 segmentos se utiliza comúnmente para mostrar números y algunos caracteres alfanuméricos.
    Este código es parte de una librería que controla el display de 7 segmentos.
*/

#include <avr/io.h>
#include <util/delay.h>

const uint8_t segment_map[16] = {
        0b00111111, // 0
        0b00000110, // 1
        0b01011011, // 2
        0b01001111, // 3
        0b01100110, // 4
        0b01101101, // 5
        0b01111101, // 6
        0b00000111, // 7
        0b01111111, // 8
        0b01101111, // 9
        0b01110111, // 10 A
        0b01111100, // 11 B
        0b00111001, // 12 C
        0b01011110, // 13 D
        0b01111001, // 14 E
        0b01110001  // 15 F
    };

void init_ports_display7seg() {
    // Configurar el puerto C como salida
    DDRC = 0xFF; // Todos los pines del puerto C como salidas
    PORTC = 0x00; // Inicializar el puerto C en bajo
}

void display_digit(uint8_t digit) {
    if (digit < 16) {
        PORTC = segment_map[digit]; // Mostrar el dígito en el display de 7 segmentos
    } else {
        PORTC = 0x00; // Si el dígito no es válido, apagar el display
    }
}
