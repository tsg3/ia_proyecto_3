#include "../include/population_manager.h"

int get_random(int min_r, int max_r) {
    int range = max_r - min_r + 1;
    return min_r + rand() % range;
}

Function* create_function(char type, int k0, int k1, int k2, int k3, int k4) {
    Function* func = NULL;
    switch (type) {
        case '0':
            func = (Function*)malloc(sizeof(Function));
            func->type = '0';
            func->k0 = (float) k0;
            func->k1 = 0;
            func->k2 = 0;
            func->k3 = 0;
            func->k4 = 0;
            break;

        case '1':
            break;

        case '2':
            break;

        case '3':
            break;

        case '4':
            break;
        
        default:
            break;
    }
    return func;
}

Individual* create_individual(char type_f, char type_g) {
    Individual* new_individual = (Individual*)malloc(sizeof(Individual));
    new_individual->next = NULL;
    new_individual->id = individuals_created;
    new_individual->fitness = 0;
    Function* new_func = NULL;
    
    // Modificar rangos de los 'get_random()' para calibrar las funciones adecuadamente
    switch (type_f) {
        case '0':
            new_func = create_function('0', get_random(0, 100), 0, 0, 0, 0);
            new_individual->f = new_func;
            break;

        case '1':
            break;

        case '2':
            break;

        case '3':
            break;

        case '4':
            break;
        
        default:
            break;
    }

    // Modificar rangos de los 'get_random()' para calibrar las funciones adecuadamente
    switch (type_g) {
        case '0':
            new_func = create_function('0', get_random(0, 100), 0, 0, 0, 0);
            new_individual->g = new_func;
            break;

        case '1':
            break;

        case '2':
            break;

        case '3':
            break;

        case '4':
            break;
        
        default:
            break;
    }

    individuals_created++;
    return new_individual;
}

void init_population(int size) {
    individuals_created = 0;

    // Funciones 0 0
    for (int _ = 0; _ < size; _++) {
        Individual* new_individual = create_individual('0', '0');

        if (first_individual != NULL) {
            last_individual->next = new_individual;
            last_individual = new_individual;
        } else {
            first_individual = new_individual;
            last_individual = new_individual;
        }
    }

    // Agregar demas configuraciones de funciones
}

float get_difference(Function* func) {
    float sum = 0;
    int i = min;
    Node* temp = data_start;
    switch (func->type) {
        case '0':
            while (temp != NULL) {
                sum += (float) pow(temp->fx - func->k0, 2);
                temp = temp->next;
            }
            break;

        case '1':
            break;

        case '2':
            break;

        case '3':
            break;

        case '4':
            break;
        
        default:
            break;
    }
    return (float) sqrt(sum);
}

void calc_fitness_temp(Individual* individual) {
    individual->fitness = get_difference(individual->f) + get_difference(individual->g);
    if (highest_fitness == -1) {
        highest_fitness = individual->fitness;
        lowest_fitness = individual->fitness;
        return;
    }
    
    if (individual->fitness > highest_fitness)
        highest_fitness = individual->fitness;
    if (individual->fitness < lowest_fitness)
        lowest_fitness = individual->fitness;
}

void calc_fitness_all() {
    Individual* temp = first_individual;
    while (temp != NULL) {
        calc_fitness_temp(temp);
        temp = temp->next;
    }
}

void selection() {
    if (selection_ptr != NULL) {
        free(selection_ptr);
    }
    int size = 25;
    int added = 0;
    selection_ptr = (Individual**)malloc(sizeof(Individual*) * size);

    Individual* temp = first_individual;
    float divisor = (highest_fitness - lowest_fitness) / 100;

    int _rand;
    bool dec;
    while (temp != NULL) {
        _rand = rand() % 101;
        dec = _rand > (temp->fitness - lowest_fitness) / divisor ? true : false;
        if (dec) {
            if (added < size) {
                *(selection_ptr + added) = temp;
                added++;
            } else {
                size += 25;
                Individual** temp_ptr = (Individual**)realloc(selection_ptr, 
                    sizeof(Individual*) * size);
                if (temp_ptr == NULL) { 
                    free(selection_ptr);
                    return;
                } 
                else {
                    selection_ptr = temp_ptr; 
                }
                *(selection_ptr + added) = temp;
                added++;
            }
        }
        temp = temp->next;
    }
    Individual** temp_ptr = (Individual**)realloc(selection_ptr, sizeof(Individual*) * added);
    if (temp_ptr == NULL) { 
        free(selection_ptr);
        return;
    } 
    else {
        selection_ptr = temp_ptr; 
    }
}

void free_individuals() {
    Individual* temp;
    while (first_individual != NULL) {
        temp = first_individual;
        first_individual = first_individual->next;
        free(temp->f);
        free(temp->g);
        free(temp);
    }
}