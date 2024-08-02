/**
 * @brief      H file for 7 segment gestion
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

#define CS          PC0
#define SS          PB2
#define MOSI        PB3
#define MISO        PB4
#define SCK         PB5
#define MAX_CHAR    16

/** Initializes the SPI as a master */
void    SPI_MasterInit_segments (void);

/** Initialises the SPI by calling the function and starts communication */
void    init7_segments          (void);

/** Sending data to the SPI */
void    spi_exchange            (char character);

/** Initializes the display */
void    init_spi                (void);

/** Displays the parameter character by sending data via the SPI */
void    loop_7segments          (char lettre);

