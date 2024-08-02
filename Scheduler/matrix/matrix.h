/**
 * @brief      H file for LED matrix
 *
 * @author     Némo CAZIN & Antoine CEGARRA
 * @date       2024
 */

/** INCLUDES */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

/** CONSTANTS */

#define CS      PC0
#define SS      PB2
#define MOSI    PB3
#define MISO    PB4
#define SCK     PB5

/** Initializes the SPI as a master */
void    SPI_MasterInit      (void);

/** Sending data to the SPI */
void    SPI_transmit        (unsigned char data);

/** Initialises the SPI by calling the function and starts communication */
void    initMatrixLED       (void);

/** Sends one bit to the SPI to control an LED */
void    sendColumn          (unsigned char data);

/** Initialise the SPI by sending the first characters required */
void    initmat             (void);

/** Sends one bit to the SPI to control an LED */
void    diplayLED           (int column);

/** Displays the letter in parameter by sending data via the SPI */
void    loop_matrix         (char letter[8]);
