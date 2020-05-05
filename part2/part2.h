//
// Created by Sujan Shrestha on 5/3/20.
//

#ifndef SSHRESTHA11_PA3_PART2_H
#define SSHRESTHA11_PA3_PART2_H

/**
 * Including all the required C libraries.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <getopt.h>
#include <string>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <ctime>
#include <random>


/**
 * Declaring the required integer variables
 */
int producer_threads_max_count;
int consumer_threads_max_count;

/**
 * Defining a global integer variable that holds the size of the buffer
 */
extern int buffer_size;

/**
 * Defining a global integer variable that holds the number of items to be produced / consumed.
 */
extern int num_of_items;

/**
 * Using namespace to define the context in which the variables, functions are defined.
 */
using namespace std;

/**
 * Defining an integer constant.
 */
#define SIZE 52

/**
 * A thread function that produces items.
 * @param threadid
 * @return
 */
void *producer(void *threadid);

/**
 * A thread function that consumes items.
 * @param threadid
 * @return
 */
void *consumer(void *threadid);

/**
 * Declaring a char array to hold uppercase and lowercase letters.
 */
char alphabet[SIZE] = {
'A', 'B', 'C', 'D', 'E', 'F', 'G',
'H', 'I', 'J', 'K', 'L', 'M', 'N',
'O', 'P', 'Q', 'R', 'S', 'T', 'U',
'V', 'W', 'X', 'Y', 'Z','a', 'b',
'c', 'd', 'e', 'f', 'g',
'h', 'i', 'j', 'k', 'l', 'm', 'n',
'o', 'p', 'q', 'r', 's', 't', 'u',
'v', 'w', 'x', 'y', 'z'};

/**
 * A function that parses the command line input, and stores values in the respective variables.
 * @param argc
 * @param argv
 */
void parseInput(int argc, char **argv);

/**
 * A function to initialize starting values for different variables
 * @return
 */
void monitor_initialize();

/**
 * A function that destroys the pre-existing semaphores.
 */
void monitor_destroy_semaphores();

/**
 * A function that inserts the input char item in the buffer vector array.
 * @param item
 * @param threadid
 */
void monitor_insert(char item, void *threadid);

/**
 * A function that removes the last item from the buffer vector array.
 * @param threadid
 */
void monitor_remove(void *threadid);

#endif //SSHRESTHA11_PA3_PART2_H
