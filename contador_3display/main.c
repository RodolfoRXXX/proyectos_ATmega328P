/*
    Proyecto que muestra un contador que crece de forma automática cada 1 segundo desde 0 hasta 255
    cuando llega a 255, empieza a decrecer hasta 0 y se repite el ciclo nuevamente
*/

#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>

uint8_t PB_salida = 0xff;
uint8_t PC_salida = 0xff;

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

// prototipo
void config_P();
void mostrarDisplay(uint8_t contador);

int main(void) {

    config_P();

    // debe entrar en un bucle tipo for o while que tenga un delay de 1seg y mostrar ese numero en un conjunto de 3 displays
    uint8_t contador = 0;
    uint8_t subiendo = 1;

    while (1) {
        mostrarDisplay(contador);

        if (subiendo) {
            if (contador < 255) {
                contador++;
            } else {
                subiendo = 0;
                contador--;
            }
        } else {
            if (contador > 0) {
                contador--;
            } else {
                subiendo = 1;
                contador++;
            }
        }
    }
}

// funciones
// función de configuración
void config_P() {
    DDRB = PB_salida;
    DDRC = PC_salida;
    PORTB |= (1 << PORTB0) | (1 << PORTB1) | (1 << PORTB2); // puerto B pines en alto, conectados al cátodo de los displays, activa cuando baja
    PORTC = 0x00;   // puerto C en baja así no hay ningún led activado
}

// función que muestra el dígito en el display
void mostrarDisplay(uint8_t contador) {
    uint8_t unidad = contador % 10;
    uint8_t decena = (contador / 10) % 10;
    uint8_t centena = contador / 100;

    uint8_t i;

    for (i = 0; i < 250; i++) { // 250 * (3*1ms) = 750ms es lo que dura el ciclo del for
        // mostrar unidad
        PORTC = display7seg[unidad]; // busca el valor en el array
        PORTB |= (1 << PORTB0) | (1 << PORTB1) | (1 << PORTB2); // desactiva los cátodos de los displays
        PORTB &= ~(1 << PORTB2);    // activa el cátodo del display
        _delay_ms(1);

        // mostrar decena
        PORTC = display7seg[decena]; // busca el valor en el array
        PORTB |= (1 << PORTB0) | (1 << PORTB1) | (1 << PORTB2); // desactiva los cátodos de los displays
        PORTB &= ~(1 << PORTB1);    // activa el cátodo del display
        _delay_ms(1);

        // mostrar centena
        PORTC = display7seg[centena]; // busca el valor en el array
        PORTB |= (1 << PORTB0) | (1 << PORTB1) | (1 << PORTB2); // desactiva los cátodos de los displays
        PORTB &= ~(1 << PORTB0);    // activa el cátodo del display
        _delay_ms(1);
    }

}