/**
 * @brief      H file for USART
 *
 * @author     Némo CAZIN & Antoine CEGARRA
 * @date       2024
 */

/** INCLUDE */
#include <string.h>

/** CONSTANT */
#define SIZE_CHAINE 1

/** Sending a character to the serial port */
void            serial_send         (unsigned char c);

/** Sending a character string on the serial port using resources */
void            serial_send_str     (char chaine[]);

/** Reading a character on the serial port */
unsigned char   serial_read         (void);

/** Reading a character string on the serial port using resources */
void            serial_read_str     (char chaine[]);
