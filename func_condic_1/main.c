/*
    Programa que tiene salidas por los puertos B y D, y entrada por el puerto C, bit 0
    funciona comparando la entrada del bit PINC0, si es alto, aumenta el contador incremento y suma 1 en la salida B
    si es bajo, resta una unidad al contador decremento y muestra la salida por D
    todo esto con un retardo de 125ms
*/

#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>

uint8_t PB_salida = 0xff;
uint8_t PC_entrada = 0x00;
uint8_t PD_salida = 0xff;

uint8_t PUA = 0xff;

int i = 0;
int d = 255;

// prototipos
void config_P();
void enviar_PB();
void enviar_PD();

int main(void) {

    // configuración inicial de puertos
    config_P();

    while (1) {
        if (!(PINC & (1 << PINC0))) {
            // PINC0 es bajo => incrementa
            i++;
            if(i == 255) {
                i = 0;
            }
            enviar_PB();
        } else {
            // PINC0 es alto => decrementa
            d--;
            if(d == 0) {
                d = 255;
            }
            enviar_PD();
        }
        _delay_ms(125);
    }
    

}

// funciones
// función configuración de puertos
void config_P() {
    DDRB = PB_salida;
    DDRC = PC_entrada;
    DDRD = PD_salida;
    PORTB = 0x00;
    PORTC = PUA;
    PORTD = 0x00;
}

void enviar_PB() {
    PORTB = i;
}

void enviar_PD() {
    PORTD = d;
}