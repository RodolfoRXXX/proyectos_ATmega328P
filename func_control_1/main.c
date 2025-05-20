/*
    Proyecto que envía por el puerto D lo que llega al puerto B mientras el valor sea menor a 128 decimal
*/

#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>

uint8_t PD_DIR = 0xff;  // puerto D dirección como salida
uint8_t PB_DIR = 0x00;  // puerto B dirección como entrada
uint8_t PUA = 0xff;     // configuro las resistencias PULL-UP como internas

// prototipos
void config_PB_PD();
void enviar_B();

int main(void) {

    // configuro los puertos
    config_PB_PD();

    // entra al ciclo y mientras los valores pasados por PORTB sean menores a 128 decimal, sigue en el bucle
    // cuando entra un valor mayor a 128, se sale del bucle y queda como está
    while (1) {
        while (PINB <= 128) {
            enviar_B();
        }
    }

}

// definición de funciones

// función configuración de puertos
void config_PB_PD() {
    DDRB = PB_DIR;
    DDRD = PD_DIR;
    PORTB = PUA;
    PORTD = 0x00;
}

// función enviar los datos desde lo que se obtiene del puerto B y se lo pasa al puerto D
void enviar_B() {
    PORTD = PINB;
}
