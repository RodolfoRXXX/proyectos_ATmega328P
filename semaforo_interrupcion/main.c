/*
  Proyecto de un semáforo
  - El semáforo tiene 3 salidas por el puerto D que son los leds de color, verde, amarillo y rojo
  - Los leds se encienden en secuencia:
                                       - Verde: 22s + 3 seg que titila
                                       - amarillo: 5s
                                       - Rojo: 30s
  - tiene dos displays que se conectan por el puerto C con multiplexado para mostrar este tiempo
  - tiene dos interrupciones en los pines PCINT 5 y PCINT 7, el pin 5 en alta pasa a rojo y pone el tiempo a 15 segundos y el pin 7
  en alta pasa a rojo y disminuye el tiempo a 10 segundos
*/

#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

uint8_t PB_salida = 0xff;
uint8_t PC_salida = 0xff;
uint8_t PD_salida = 0xff;
uint8_t estado = 0;

const uint8_t dig7seg[] = {
    0b00011111, // 0
    0b00000110, // 1
    0b01011011, // 2
    0b01001111, // 3
    0b01100110, // 4
    0b01101101, // 5
    0b01111101, // 6
    0b00000111, // 7
    0b01111111, // 8
    0b01100111  // 9
};


// prototipos
void config_P();
void conteo(uint8_t tiempo);

int main(void) {

    config_P();

    cli();

    // habilitamos el conjunto 0 de los pines(5 y 7) 
    PCICR = (1 << PCIE0);
    // habilitamos los pines específicos 5 y 7 para detectar interrupciones
    PCMSK0 = (1 << PCINT7) | (1 << PCINT5);

    sei();

    uint8_t i;

    while (1) {
      if (estado == 0) {
        // Rojo
        PORTD &= ~((1 << PORTD0) | (1 << PORTD1) | (1 << PORTD2)); // limpia los estados de las tres salidas del puerto D
        PORTD = (1 << PORTD0);
        for (i = 30; i > 0; i--) {
          conteo(i);
        }
        estado = 1;
      } else if (estado == 1) {
        // Amarillo
        PORTD &= ~((1 << PORTD0) | (1 << PORTD1) | (1 << PORTD2));  // limpia los estados de las tres salidas del puerto D
        PORTD = (1 << PORTD1);
        for (i = 5; i > 0; i--) {
          conteo(i);
        }
        estado = 2;
      } else {
        // Verde
        PORTD &= ~((1 << PORTD0) | (1 << PORTD1) | (1 << PORTD2));  // limpia los estados de las tres salidas del puerto D
        PORTD = (1 << PORTD2);
        for (i = 25; i > 0; i--) {
          conteo(i);
        }
        estado = 0;
      }
    }
}

// funciones
// función configuración
void config_P() {
    DDRD = PD_salida;
    DDRB = PB_salida;
    DDRC = PC_salida;
    PORTD = 0x00;
    PORTB = PORTB |= (1 << PORTB0) | (1 << PORTB1);
    PORTC = 0x00;
}

// funciones para encender LED semáforo
// función que muestra el dígito en el display
void conteo(uint8_t tiempo) {
    uint8_t unidad = tiempo % 10;
    uint8_t decena = tiempo / 10;

    uint8_t i;

    for (i = 0; i < 500; i++) { // 250 * (2*1ms) = 500ms es lo que dura el ciclo del for
        // mostrar unidad
        PORTC = dig7seg[unidad]; // busca el valor en el array
        PORTB |= (1 << PORTB0) | (1 << PORTB1); // desactiva los cátodos de los displays
        PORTB &= ~(1 << PORTB1);    // activa el cátodo del display
        _delay_ms(1);

        // mostrar decena
        PORTC = dig7seg[decena]; // busca el valor en el array
        PORTB |= (1 << PORTB0) | (1 << PORTB1); // desactiva los cátodos de los displays
        PORTB &= ~(1 << PORTB0);    // activa el cátodo del display
        _delay_ms(1);
    }
}

ISR(PCINT0_vect) {
  estado = 0;  // Reinicia al estado ROJO si hay interrupción
}