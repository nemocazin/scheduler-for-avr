/**
 * @brief      C file for the scheduler
 *
 * @author     Némo CAZIN & Antoine CEGARRA
 * @date       2024
 */

#include "ordonnanceur.h"

ISR(TIMER1_COMPA_vect,ISR_NAKED);

int actuel = 0; 
int sem_writing = 1;
int sem_reading = 1;

Task tasks[MAX_TASKS] = {
                         {led_1, WORKING, 0x0600, 0, DELAY},
                         {led_2, WORKING, 0x0625, 0, DELAY},
                         //{serie_send, WORKING, 0x0700, 0, DELAY},
                         {serie_read, WORKING, 0x0700, 0, DELAY},
                         //{matrix_set, WORKING, 0x0740, 0, DELAY},
                         {set_7segments, WORKING, 0x0780, 0, DELAY},
                         {task_always_on, WORKING, 0x0800, 0, DELAY} // DO NOT EXCEED 0X0800
                        };
    
void init_timer(void){
    TCCR1A = 0;  // No output pin connected, no PWM mode enabled
    TCCR1B = 1<<CTC1; // No input pin used, clear timer counter on compare match
    #if (PRESCALER==8)
    TCCR1B |= (1<<CS11);
    #endif
    #if (PRESCALER==64)
    TCCR1B |= (1<<CS11 | 11<<CS10);
    #endif
    #if (PRESCALER==256)
    TCCR1B |= (1<<CS12);
    #endif
    #if (PRESCALER==1024)
    TCCR1B |= (1<<CS12 | 1<<CS10);
    #endif
    OCR1A = NB_TICK;
    TCNT1 = 0;
    TIMSK1 = (1<<OCIE1A); // No overflow mode enabled, no input interrupt, output compare interrupt
}

void init_ports(void){
    DDRD |= 0x80;
    DDRC |= 0x01;
}

void init_usart(long int speed){
    UBRR0 = FREQUENCE/((unsigned long int)speed << 4) -1;
    UCSR0B = (1 << TXEN0 | 1 << RXEN0);
    UCSR0C = (1 << UCSZ01 | 1 << UCSZ00);
    UCSR0A &= ~(1 << U2X0);
}

void init_task(int num){
    int save_SP = SP;
    SP = tasks[num].StackPointeur;
    uint16_t adresse = (uint16_t)tasks[num].fonction;
    asm volatile(
        "push %0 \n\t" : : "r" (adresse & 0x00ff) 
    );
    asm volatile(
        "push %0 \n\t" : : "r" ((adresse & 0xff00)>>8) 
    );
    portSAVE_CONTEXT();
    tasks[num].StackPointeur = SP;
    SP = save_SP;
}

void semaphore_write(int action){
    if(action == TAKE_RESOURCE){
        while(1){
            cli();
            
            /** Available Resources */
            if(sem_writing > 0){
                sem_writing = 0;
                sei();
                break;
            }
            
            /** Occupied resource */
            else{
                tasks[actuel].reason = WORKING;
                tasks[actuel].state = SLEEPING;
                TCNT1 = 0;
                TIMER1_COMPA_vect();
            }
        sei();
        while(sem_writing == 0);
        }
    }
    if(action == DROP_RESOURCE){
        cli();
        sem_writing = 1;
        sei();
    }
}


void semaphore_read(int action){
    if(action == TAKE_RESOURCE){
        while(1){
            cli();
            
            /** Available Resources */
            if(sem_reading > 0){
                sem_reading = 0;
                sei();
                break;
            }
            
            /** Occupied resource */
            else{
                tasks[actuel].reason = WORKING;
                tasks[actuel].state = SLEEPING;
                TCNT1 = 0;
                TIMER1_COMPA_vect();
            }
        sei();
        while(sem_reading == 0);
        }
    }
    if(action == DROP_RESOURCE){
        cli();
        sem_reading = 1;
        sei();
    }
}


void scheduler(void){
    for(int i = 0; i < MAX_TASKS; i++){
        if(tasks[i].state == SLEEPING && tasks[i].reason == DELAY){
            uint16_t time = 20;
            if(TCNT1 != 0){
                time = TCNT1 * 200 / OCR1A / 10;
                TCNT1 = 0;
            }
            tasks[i].duration = tasks[i].duration - time;
            if(tasks[i].duration == 0) { tasks[i].state = WORKING; }
        }       
    }
    
    do{
        actuel++;
        if(actuel == MAX_TASKS) { actuel = 0; }
    } while(tasks[actuel].state == SLEEPING);
}

void pause(int time){
    cli();
    tasks[actuel].state = SLEEPING;
    tasks[actuel].reason = DELAY;
    tasks[actuel].duration = time;
    TCNT1 = 0;
    sei();
    TIMER1_COMPA_vect();
}

ISR(TIMER1_COMPA_vect,ISR_NAKED){
    /* Saving the context of the interrupted task */
    portSAVE_CONTEXT();
    tasks[actuel].StackPointeur = SP;
    /* Calling the scheduler */
    scheduler();
    /* Recovering the context of the reactivated task */
    SP = tasks[actuel].StackPointeur;
    portRESTORE_CONTEXT();
    asm volatile ("reti");
}

int main(void){
    init_usart(BAUD_RATE);
    init_ports();
    init_timer();
    /* Initialising the task */
    for(int i = 0; i < MAX_TASKS; i++) { init_task(i); }
    sei();
    SP = tasks[actuel].StackPointeur;
    tasks[actuel].fonction();
    return 0;
}
