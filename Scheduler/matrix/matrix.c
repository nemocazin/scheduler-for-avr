/**
 * @brief      C file for LED matrix
 *
 * @author     Némo CAZIN & Antoine CEGARRA
 * @date       2024
 */

#include "matrix.h"

void SPI_MasterInit(void){
    DDRB |= (1 << MOSI) | (1 << SCK) | (1 << SS);
    DDRC |= (1 << CS);
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
}

void SPI_transmit(unsigned char data){
    SPDR = data;
    while(!(SPSR & (1 << SPIF)));
}

void initMatrixLED(void){
    SPI_MasterInit();
    PORTC |= (1 << CS);
}

void sendColumn(unsigned char data){
    SPI_transmit(data);
}

void initmat(void){
    PORTC &= ~(1 << CS);
    SPI_transmit('%');
    SPI_transmit(1);
    PORTC |= (1 << CS);
}

void diplayLED(int column){
    sendColumn(column);
}

void loop_matrix(char letter[8]){
    int temp;
    PORTC &= ~(1 << CS);
    for(short int i = 0; i < 8; i++){
            
        for(short int j = 0; j < 8; j++)
        {
            temp = letter[i] & (1 << j); 
            diplayLED(temp); // Sending each bit on the SPI
        }
    }
    PORTC |= (1 << CS);
}

