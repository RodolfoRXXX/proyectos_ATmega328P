/*
    * @file display7seg.c
    * @brief Functions to control a 7-segment display.
    *
    * @version 1.0
    * @date 2023-10-01
    * @author YRodolfo Romero
    *
    * Función main para el control de un display de 7 segmentos
    * utilizando un teclado matricial 4x4.
    * El display muestra el valor de la tecla presionada en el teclado.
    * El teclado está conectado a un microcontrolador AVR y el display a los pines
    * del puerto C del microcontrolador.
    * El código configura los pines del puerto C como salidas y utiliza un mapa de
    * segmentos para mostrar los dígitos del 0 al 9 y de A a F en el display de 7 segmentos.
    * El teclado matricial 4x4 está conectado a los pines del puerto D del microcontrolador.
    * El código escanea el teclado activando cada fila y leyendo las columnas para detectar
    * qué teclas están presionadas. Si una columna está en bajo, se considera que
    * la tecla correspondiente está presionada. El código puede ser modificado para realizar
    * acciones específicas cuando se detecta una tecla presionada,
    * como imprimir el valor de la tecla en el display de 7 segmentos.
*/

#define F_CPU 1000000UL // Frecuencia del reloj del microcontrolador

#include <avr/io.h>
#include <util/delay.h>
#include "../display_7segmentos/display7seg.h"
#include "../teclado_matricial_4x4/keypad.h"

void init() {
    // Inicializar los puertos
    init_ports_display7seg();
    init_port_keypad();
}

void main(void) {
    init(); // Inicializar los puertos

    while (1) {
        uint8_t key = scan_keypad(); // Escanear el teclado matricial 4x4

        if (key < 16) { // Verificar si la tecla presionada es válida
            display_digit(key); // Mostrar el dígito en el display de 7 segmentos
        } else {
            display_digit(0xFF); // Apagar el display si la tecla no es válida
        }

        _delay_ms(200); // Esperar un tiempo para evitar rebotes
    }
}

// Fin del archivo main.c