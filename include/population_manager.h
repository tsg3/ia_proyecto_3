#ifndef POPULATION_MANAGER_H_
#define POPULATION_MANAGER_H_

#include <time.h>
#include <math.h>
#include "data_manager.h"

typedef struct Function {
    char type;
    float k0;
    float k1;
    float k2;
    float k3;
    float k4;
} Function;

typedef struct Individual {
    Function* f;
    Function* g;
    struct Individual* next;
    int id;
    float fitness;
} Individual;

Individual* first_individual;
Individual* last_individual;
int individuals_created;
int max_population;
int min;
float highest_fitness;
float lowest_fitness;

Individual** selection_ptr;

Function* create_function(char, int, int, int, int, int);
Individual* create_individual(char, char);

int get_random(int, int);
void init_population(int);
void free_individuals();
float get_difference(Function*);
void calc_fitness_temp(Individual*);
void calc_fitness_all();
void selection();

#endif