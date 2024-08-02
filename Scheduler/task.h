/**
 * @brief      H file for all the tasks
 *
 * @author     Némo CAZIN & Antoine CEGARRA
 * @date       2024
 */

/** INCLUDES */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

/** CONSTANTS */

#define WORKING         1
#define SLEEPING        0 
#define DELAY           3
#define SIZE_CHAINE     1

/** Task to light the first LED */
void    led_1               (void);

/** Task to light the second LED */
void    led_2               (void);

/** Task for sending data on the serial port */
void    serie_send          (void);

/** Task for reading data on the serial port */
void    serie_read          (void);

/** Task for using the LED matrix with the SPI */
void    matrix_set          (void);

/** Task for using the 7-segment display with the SPI */
void    set_7segments       (void);

/** Loop task */
void    task_always_on      (void);
