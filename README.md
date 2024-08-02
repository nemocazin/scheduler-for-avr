# Scheduler

## Table of content

 * [General project information](#general-project-information)
 * [Technologies used](#technologies-used)
 * [Usage](#usage)
 * [Task description](#task-description)
 * [Contact](#contact)

## General project information

This project was carried out as part of the Systems and Networks practical course in semester 7 of the Embedded Systems course. I worked with an anothr student, Antoine Cegarra.
For this scheduler, we use an ISR to execute tasks in a loop. Tasks are defined a structure and their execution time is managed by a pause function. Some tasks use semaphores, since they use the same resource. 
The scheduler works with an Arduino Uno mounted with a Shield card.

## Technologie used

This program only uses the C programming language

## Usage

To use our program, you need to : 
 * Compile all the files : _"make"_
 * Send program to Arduino Uno board (connected to computer)  : _"make upload"_

 Not all tasks are initialized and run at the same time. If you want to change the tasks, in the "ordonnanceur.c" file you must comment out one of the two tasks between :
  * serie_send and serie_read
  * matrix_set and set_7segments

## Task description 

All task information is available in the "task.c" file.

## Contact

Created by [@nemocazin] & Antoine Cegarra