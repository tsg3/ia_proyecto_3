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
    struct Individual* prev;
    int id;
    float fitness;
    int age;
} Individual;

int first_x;
int first_y;
int last_x;
int last_y;
int approx_m;
int life_span;

Individual* first_individual;
Individual* last_individual;
int individuals_created;
int max_population;
float highest_fitness;
float lowest_fitness;
float mutation_prob;
int generations;
int size_population;

Individual** selection_ptr;
int selected;
Individual** crossover_ptr;
Individual** new_offspring;
int size_offspring;
int limit_offspring;

Function* create_function(char, float, float, float, float, float);
Individual* create_individual(char, char);

void init_population();
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
void mutation_temp(Individual*, float);

void grow_up();
bool kill_old();
void reorder_population();
void add_diversity();
float sigmoid(int);

void clean_similar(int);
void re_fill_population();

// test

void print_population();

#endif