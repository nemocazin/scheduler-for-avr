/**
 * @brief      C file for USART
 *
 * @author     Némo CAZIN & Antoine CEGARRA
 * @date       2024
 */

#include "usart.h"
#include "ordonnanceur.h"

void serial_send(unsigned char c){
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = c;
}


void serial_send_str(char chaine[]){
    semaphore_write(TAKE_RESOURCE);
    for(int i = 0; i < SIZE_CHAINE; i++){
        serial_send(chaine[i]);
    }
    semaphore_write(DROP_RESOURCE);   
}


unsigned char serial_read(void){
    loop_until_bit_is_set(UCSR0A, RXC0);
    return UDR0;
}


void serial_read_str(char chaine[]){
    semaphore_read(TAKE_RESOURCE);
    for(int i = 0; i < SIZE_CHAINE; i++){
        chaine[i] = serial_read();
    }
    semaphore_read(DROP_RESOURCE);   
}
