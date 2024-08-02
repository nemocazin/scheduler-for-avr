/**
 * @brief      H file for the scheduler
 *
 * @author     Némo CAZIN & Antoine CEGARRA
 * @date       2024
 */

/** INCLUDES */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "task.h"
#include "usart.h"

/** CONSTANTS */

#define FREQUENCE           16000000
#define BAUD_RATE           9600
#define PRESCALER           1024
#define NB_TICK             312
#define CTC1                WGM12  // Better name

#define MAX_TASKS           5
#define TASK_STACK_SIZE     32

#define TAKE_RESOURCE       1
#define DROP_RESOURCE       0

/** Task structure */
typedef struct{
    void (*fonction)(void);
    uint8_t state;
    uint16_t StackPointeur;
    int duration;
    uint8_t reason;
} Task;


/** Function for saving the initial context */
#define portSAVE_CONTEXT() \
asm volatile ( \
    "push r0 \n\t" \
    "in r0, __SREG__ \n\t" \
    "push r0 \n\t" \
    "push r1 \n\t" \
    "push r2 \n\t" \
    "push r3 \n\t" \
    "push r4 \n\t" \
    "push r5 \n\t" \
    "push r6 \n\t" \
    "push r7 \n\t" \
    "push r8 \n\t" \
    "push r9 \n\t" \
    "push r10 \n\t" \
    "push r11 \n\t" \
    "push r12 \n\t" \
    "push r13 \n\t" \
    "push r14 \n\t" \
    "push r15 \n\t" \
    "push r16 \n\t" \
    "push r17 \n\t" \
    "push r18 \n\t" \
    "push r19 \n\t" \
    "push r20 \n\t" \
    "push r21 \n\t" \
    "push r22 \n\t" \
    "push r23 \n\t" \
    "push r24 \n\t" \
    "push r25 \n\t" \
    "push r26 \n\t" \
    "push r27 \n\t" \
    "push r28 \n\t" \
    "push r29 \n\t" \
    "push r30 \n\t" \
    "push r31 \n\t" \
    );


/** Function to restore the initial context */
#define portRESTORE_CONTEXT() \
asm volatile ( \
    "pop r31 \n\t" \
    "pop r30 \n\t" \
    "pop r29 \n\t" \
    "pop r28 \n\t" \
    "pop r27 \n\t" \
    "pop r26 \n\t" \
    "pop r25 \n\t" \
    "pop r24 \n\t" \
    "pop r23 \n\t" \
    "pop r22 \n\t" \
    "pop r21 \n\t" \
    "pop r20 \n\t" \
    "pop r19 \n\t" \
    "pop r18 \n\t" \
    "pop r17 \n\t" \
    "pop r16 \n\t" \
    "pop r15 \n\t" \
    "pop r14 \n\t" \
    "pop r13 \n\t" \
    "pop r12 \n\t" \
    "pop r11 \n\t" \
    "pop r10 \n\t" \
    "pop r9 \n\t" \
    "pop r8 \n\t" \
    "pop r7 \n\t" \
    "pop r6 \n\t" \
    "pop r5 \n\t" \
    "pop r4 \n\t" \
    "pop r3 \n\t" \
    "pop r2 \n\t" \
    "pop r1 \n\t" \
    "pop r0 \n\t" \
    "out __SREG__, r0 \n\t" \
    "pop r0 \n\t" \
    );

/** Timer initialisation */
void    init_timer          (void);

/** Initialisation of LED ports */
void    init_ports          (void);

/** Initialising the serial link */
void    init_usart          (long int speed);

/** Initialising tasks */
void    init_task           (int num);

/** Semaphore for writing */
void    semaphore_write     (int action);

/** Semaphore for reading */
void    semaphore_read      (int action);

/** Task management scheduler */
void    scheduler           (void);

/** Task pause function */
void    pause               (int time);
