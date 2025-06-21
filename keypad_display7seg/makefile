# Configuración general
MCU = atmega328p
F_CPU = 1000000UL
CC = avr-gcc
CFLAGS = -std=c99 -Os -DF_CPU=$(F_CPU) -mmcu=$(MCU)

# Archivos fuente
SRCS = main.c \
       drivers/keypad_4x4/keypad.c \
       drivers/display_7seg/display7seg.c

# Archivos objeto generados automáticamente a partir de los .c
OBJS = $(SRCS:.c=.o)

# Nombre del ejecutable
TARGET = programa

# Regla por defecto
all: $(TARGET).hex

# Enlazado
$(TARGET).elf: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Conversión a .hex
$(TARGET).hex: $(TARGET).elf
	avr-objcopy -O ihex -R .eeprom $< $@

# Compilación de .c a .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpiar archivos intermedios
clean:
	rm -f $(OBJS) $(TARGET).elf $(TARGET).hex

# Subir al microcontrolador (editá según tu programador)
upload: $(TARGET).hex
	avrdude -c usbasp -p m328p -U flash:w:$(TARGET).hex

