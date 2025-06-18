/*
    Teclado matricial 4x4
    Este programa permite leer un teclado matricial 4x4 y mostrar el valor de la tecla presionada en el display.
*/

#include <avr/io.h>
#include <util/delay.h>

void init_ports() {
    // Configurar filas como salidas
    DDRD |= 0x0F; // PD0 a PD3 como salidas(0000 1111)
    // Configurar columnas como entradas con pull-up
    DDRD &= ~0xF0; // PD4 a PD7 como entradas((0000 1111)&(0000 1111) = 0000 1111)
    PORTD |= 0xF0; // Habilitar pull-up en PD4 a PD7(1111 0000)
}

void scan_keypad() {
    for (uint8_t row = 0; row < 4; row++) {
        // Activar fila
        PORTD &= ~(1 << row); // Poner fila en bajo
        _delay_ms(10); // Esperar estabilización

        // Leer columnas
        uint8_t cols = PIND & 0xF0; // Leer PD4 a PD7

        if (cols != 0xF0) { // Si alguna columna está en bajo
            for (uint8_t col = 0; col < 4; col++) {
                if (!(cols & (1 << (col + 4)))) { // Verificar si la columna está en bajo
                    // Aquí se puede procesar la tecla presionada
                    // Por ejemplo, imprimir el valor de la tecla
                }
            }
        }

        // Desactivar fila
        PORTD |= (1 << row); // Poner fila en alto
    }
}