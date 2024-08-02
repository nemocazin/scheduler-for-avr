/**
 * @brief      C file for 7 segment gestion
 *
 * @author     Némo CAZIN & Antoine CEGARRA
 * @date       2024
 */

#include "7_segments.h"

void SPI_MasterInit_segments(void){
    DDRB |= (1 << MOSI) | (1 << SCK) | (1 << SS);
    DDRC |= (1 << CS);
    PORTB |= (1 << SS);
    PORTC |= (1 << CS);
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0) | (1 << SPR1);   
}


void init7_segments(void){
    SPI_MasterInit_segments();
    PORTC |= (1 << CS);
}


void spi_exchange(char character)
{
SPDR = character;
while(!(SPSR & (1<<SPIF)));
}


void init_spi(void){
    PORTC &= ~(1 << CS);
    spi_exchange(0x76);     // 0 on all segments
    PORTC |= (1 << CS);
}


void loop_7segments(char lettre){
    PORTC &= ~(1 << CS);
    spi_exchange(lettre);
    PORTC |= (1 << CS);
} 

