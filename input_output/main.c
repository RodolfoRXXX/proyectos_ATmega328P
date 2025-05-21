/*
    Proyecto que toma la entrada del puerto D en binario y responde desde el puerto C encendiendo un display de 8 segmentos

    1 - 0b00000001 = 0000110
    2 - 0b00000010 = 1011011
    3 - 0b00000011 = 1001111
    4 - 0b00000100 = 1100110
    5 - 0b00000101 = 1101101
    6 - 0b00000110 = 1111101
    7 - 0b00000111 = 0000111
    8 - 0b00001000 = 1111111
    9 - 0b00001001 = 1101111
*/

#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>

typedef struct {
    uint8_t entrada;
    uint8_t display;
} tablaDisplay;

const tablaDisplay tabla[] = {
    {0b00000000, 0b00111111},   // 0
    {0b00000001, 0b00000110},   // 1
    {0b00000010, 0b01011011},   // 2
    {0b00000011, 0b01001111},   // 3
    {0b00000100, 0b01100110},   // 4
    {0b00000101, 0b01101101},   // 5
    {0b00000111, 0b01111101},   // 6
    {0b00001000, 0b00000111},   // 7
    {0b00001001, 0b01111111},   // 8
    {0b00001010, 0b01101111}    // 9
};

#define TAM_TABLA (sizeof(tabla)/sizeof(tabla[0]))

uint8_t PD_entrada = 0x00;  //0b00000000
uint8_t PC_salida = 0xff;   //0b11111111
uint8_t PUA = 0xff;         //0b11111111

// prototipos
void config_P();

int main(void) {
    // configurar puertos
    config_P();

    while (1) {
        uint8_t entrada = PIND;

        // Busca en el array en elemento ingresado en el puerto
        uint8_t encontrado = 0;
        uint8_t i;

        for (i = 0; i < TAM_TABLA; i++)
        {
            if (entrada == tabla[i].entrada) {
                PORTC = tabla[i].display;
                encontrado = 1;
                break;
            }
        }

        // apaga display si no encuentró el valor
        if (!encontrado) {
            PORTC = 0x00;
        }
        
        _delay_ms(100);
    }
    
}

// funciones
// función para configurar los puertos
void config_P() {
    DDRD = PD_entrada;
    DDRC = PC_salida;
    PORTD = PUA;
    PORTC = 0x00;
}

// función para tomar datos del puerto de entrada y devuelve el resultado a mostrar por el display
void mostrarDigito() {

}