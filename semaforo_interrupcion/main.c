/*
  Proyecto de un semáforo
  - El semáforo tiene 3 salidas por el puerto D que son los leds de color, verde, amarillo y rojo
  - Los leds se encienden en secuencia:
                                       - Verde: 22s + 3 seg que titila
                                       - amarillo: 5s
                                       - verde: 30s
  - tiene dos displays que se conectan por el puerto C con multiplexado para mostrar este tiempo
  - tiene dos interrupciones en los pines PCINT 5 y PCINT 7, el pin 5 en alta pasa a rojo y pone el tiempo a 15 segundos y el pin 7
  en alta pasa a rojo y disminuye el tiempo a 10 segundos
*/

#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

uint8_t PD_salida = 0x00;
uint8_t PB_salida = 0xff;

uint8_t dig7seg[] = {
    {0b00011111}, // 0
    {0b00000110}, // 1
    {0b01011011}, // 2
    {0b01001111}, // 3
    {0b01100110}, // 4
    {0b01101101}, // 5
    {0b01111101}, // 6
    {0b00000111}, // 7
    {0b01111111}, // 8
    {0b01100111}  // 9
};


// prototipos
void config_P();
void mostrarDisplay(uint8_t contador);

int main(void) {

    config_P();

    cli();

    // habilitamos el conjunto 0 de los pines(5 y 7) 
    PCICR = (1 << PCIE0);
    // habilitamos los pines específicos 5 y 7 para detectar interrupciones
    PCMSK0 = (1 << PCINT7) | (1 << PCINT0);

    sei();

    uint8_t estado = 0;
    uint8_t identificador;
    uint8_t i;

    while (1) {
      if ((estado = 0)) {
        PORTD &= (1 << PORTD0) & (1 << PORTD1) & (1 << PORTD2);  // limpia todos los leds
        PORTD = (1 << PORTD0);
        for (i = 0; i < 25; i++) {
            _delay_ms(1000);
        }
        estado = 1;

      }
      if ((estado = 1)) {
        
      }
      if ((estado = 2)) {
        
      }

    }
}

// funciones
// función configuración
void config_P() {
    DDRD = PD_salida;
    DDRB = PB_salida;
    PORTB = 0x00;
    PORTD = 0x00;
}

// funciones para encender LED semáforo
// función que muestra el dígito en el display
void mostrarDisplay(uint8_t contador) {
    uint8_t unidad = contador % 10;
    uint8_t decena = contador / 10;

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
    }

}