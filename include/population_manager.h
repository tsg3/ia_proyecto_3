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
int individuals_created;
int max_population;
int min;
float highest_fitness;
float lowest_fitness;
int mutation_prob;
int generations;

Individual** selection_ptr;
int selected;
Individual** crossover_ptr;
Individual** new_offspring;
int size_offspring;
int limit_offspring;

Function* create_function(char, int, int, int, int, int);
Individual* create_individual(char, char);

int get_random(int, int);
void init_population(int);
void free_individuals();
float get_difference(Function*);
void calc_fitness_temp(Individual*);

void selection();
void mix_genes(Individual*, Individual*, Individual*, Individual*, bool, bool, bool, bool);
void crossover_temp(Individual*, Individual*);
void crossover();
void calc_fitness_offspring();
void compute_mutations();
void add_offspring();
void mutation_temp(Individual*);

// test

void print_population();

#endif