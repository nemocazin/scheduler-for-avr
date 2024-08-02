/**
 * @brief      C file for all the tasks
 *
 * @author     Némo CAZIN & Antoine CEGARRA
 * @date       2024
 */

#include "task.h"
#include "ordonnanceur.h"
#include "matrix/matrix.h"
#include "7_segments/7_segments.h"

char chaine[SIZE_CHAINE+1];
char lettre[1];
int size = 3;

/** Variables for displaying characters on the LED matrix */
char letterA[8] = {
    0b00111100,
    0b01100110,
    0b11000011,
    0b11000011,
    0b11111111,
    0b11000011,
    0b11000011,
    0b11000011
};

char letterB[8] = {
    0b11111111,
    0b11000011,
    0b11000011,
    0b11000110,
    0b11111111,
    0b11000110,
    0b11000011,
    0b11111111
};

char letterC[8] = {
    0b00111100,
    0b01111000,
    0b01100000,
    0b11000000,
    0b11000000,
    0b01100000,
    0b01111000,
    0b00111100
}; 

char num1[8] = {
    0b00011000,
    0b01111000,
    0b11011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b11111111
};

char num2[8] = {
    0b11111111,
    0b00000001,
    0b00000001,
    0b00000001,
    0b11111111,
    0b10000000,
    0b10000000,
    0b11111111
};

/** Functions */

void led_1(void){
    while(1){
        PORTD ^= 0x80;
        pause(500);
    }
}

void led_2(void){
    while(1){
        PORTC ^= 0x01;
        pause(200);
    }
}

void serie_send(void){
    while(1){
        serial_send_str("abc\r\n");
        pause(200);
    }
}

void serie_read(void){
    while(1){
        serial_read_str(chaine);    // Reading 
        serial_send_str(chaine);    // Writing for verification
        chaine[SIZE_CHAINE]='\0';
        pause(100);
    }
}

void matrix_set(void){
    char letter[8] = {0};
    initMatrixLED();
    initmat();
    while(1){
        if(chaine[0] == 'a') {strcpy(letter, letterA); loop_matrix(letter);}
        if(chaine[0] == 'b') {strcpy(letter, letterB); loop_matrix(letter);}
        if(chaine[0] == 'c') {strcpy(letter, letterC); loop_matrix(letter);}
        if(chaine[0] == '1') {strcpy(letter, num1); loop_matrix(letter);}
        if(chaine[0] == '2') {strcpy(letter, num2); loop_matrix(letter);}
        pause(50);
    }
}


void set_7segments(void) {
    init7_segments();
    init_spi();
    while(1){
        loop_7segments(chaine[0]);
        pause(100);
    }
}

void task_always_on(void){
    while(1){
        _delay_ms(50);
    }
}

