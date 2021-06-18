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

int first_x;
int first_y;
int last_x;
int last_y;
int approx_m;

Individual* first_individual;
int individuals_created;
int max_population;
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

Function* create_function(char, float, float, float, float, float);
Individual* create_individual(char, char);

void init_population(int);
void free_individuals();
float get_value(Function*, int);
float get_difference(Individual*);
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