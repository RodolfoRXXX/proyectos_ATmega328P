/*
    Programa que entrega una señal PWM regulable con potenciómetro.
    La señal PWM se obtiene desde el pin PD6, que es el pin OC0A del
    microcontrolador ATmega328P. El potenciómetro se conecta al pin ADC0
    (PA0) y se utiliza para ajustar el ciclo de trabajo de la señal PWM.
*/

#define F_CPU 16000000UL // Frecuencia del reloj del microcontrolador

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void initADC(void) {
    // Configurar el ADC
    ADMUX = (1 << REFS0); // Referencia de voltaje AVcc, canal ADC0
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1); // Habilitar ADC y prescaler 64
}

void initPWM(void) {
    // Configurar el pin PD6 como salida
    DDRD |= (1 << PD6);
    
    // Configurar el Timer 0 en modo Fast PWM, no invertido
    TCCR0A = (1 << WGM00) | (1 << WGM01) | (1 << COM0A1);
    TCCR0B = (1 << CS00); // Prescaler 1
}

uint16_t readADC(void) {
    // Seleccionar el canal ADC0
    ADMUX = (ADMUX & 0xF0) | (0 & 0x0F);
    
    // Iniciar la conversión
    ADCSRA |= (1 << ADSC);
    
    // Esperar a que la conversión termine
    while (ADCSRA & (1 << ADSC));
    
    // Retornar el valor del ADC
    return ADC;
}

void setPWM(uint8_t dutyCycle) {
    // Ajustar el valor del registro OCR0A para establecer el ciclo de trabajo
    OCR0A = dutyCycle;
}

int main(void) {
    initADC(); // Inicializar el ADC
    initPWM(); // Inicializar el PWM
    
    while (1) {
        // Leer el valor del potenciómetro
        uint16_t adcValue = readADC();
        
        // Mapear el valor del ADC (0-1023) al ciclo de trabajo del PWM (0-255)
        uint8_t dutyCycle = adcValue / 4; // 1023/4 = 255
        
        // Establecer el ciclo de trabajo del PWM
        setPWM(dutyCycle);
        
        _delay_ms(100); // Esperar un poco antes de la siguiente lectura
    }
}

// Fin del programa
// Este programa genera una señal PWM en el pin PD6 del ATmega328P