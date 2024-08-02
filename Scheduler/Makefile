##
 # @brief      Makefile
 #
 # @author     Némo CAZIN & Antoine CEGARRA
 # @date       2024
 #/

CC = avr-gcc -mmcu=atmega328p -DF_CPU=16000000UL
CFLAGS = -Wall 
TARGET = ordonnanceur

default: 
	avr-gcc -mmcu=atmega328p -DF_CPU=16000000UL -c -Wall -I. -Os $(TARGET).c -o $(TARGET).o
	avr-gcc -mmcu=atmega328p -DF_CPU=16000000UL -c -Wall -I. -Os task.c -o task.o
	avr-gcc -mmcu=atmega328p -DF_CPU=16000000UL -c -Wall -I. -Os usart.c -o usart.o
	avr-gcc -mmcu=atmega328p -DF_CPU=16000000UL -c -Wall -I. -Os matrix/matrix.c -o matrix/matrix.o
	avr-gcc -mmcu=atmega328p -DF_CPU=16000000UL -c -Wall -I. -Os 7_segments/7_segments.c -o 7_segments/7_segments.o
	avr-gcc -mmcu=atmega328p -g -lm -Wl,--gc-sections -o $(TARGET).elf $(TARGET).o task.o usart.o matrix/matrix.o 7_segments/7_segments.o

upload:
	$ avr-objcopy -j .text -j .data -O ihex $(TARGET).elf $(TARGET).hex
	$ stty -F /dev/ttyUSB0 hupcl
	$ avrdude -F -v -p atmega328p -c stk500v1 -b 115200 -P /dev/ttyUSB0 -U flash:w:$(TARGET).hex
	
clean:
	rm -f $(TARGET) *.elf *.hex *.o matrix/matrix.o 7_segments/7_segments.o 
