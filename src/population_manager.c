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
    calc_fitness_temp(new_individual);

    individuals_created++;
    return new_individual;
}

void init_population(int size) {
    individuals_created = 0;

    // Funciones 0 0
    for (int _ = 0; _ < size; _++) {
        Individual* new_individual = create_individual('0', '0');

        if (first_individual == NULL) first_individual = new_individual;
        else {
            if(first_individual->fitness < new_individual->fitness){
                new_individual->next = first_individual;
                first_individual = new_individual;
            } else {
                Individual* prev = first_individual;
                Individual* temp = prev->next;
                while(temp != NULL) {
                    if(temp->fitness < new_individual->fitness) break;
                    prev = temp;
                    temp = temp->next;
                }
                prev->next = new_individual;
                new_individual->next = temp;
            }
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

void selection() {
    int size = 25;
    selected = 0;
    selection_ptr = (Individual**)malloc(sizeof(Individual*) * size);

    Individual* temp = first_individual;
    float divisor = (highest_fitness - lowest_fitness) / 100;

    int _rand;
    bool dec;
    while (temp != NULL) {
        _rand = rand() % 101;
        dec = _rand > 33 + (temp->fitness - lowest_fitness) / divisor ? true : false; // modificar
        if (dec) {
            if (selected >= size) {
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
            }
            *(selection_ptr + selected) = temp;
            selected++;
        }
        temp = temp->next;
    }
    Individual** temp_ptr = (Individual**)realloc(selection_ptr, sizeof(Individual*) * selected);
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

void mix_genes(Individual* par_a, Individual* par_b, Individual* off_a, Individual* off_b, 
        bool _a, bool _b, bool _c, bool _d) {
    int choice;
    off_a->f->k0 = par_a->f->k0;
    off_a->f->k1 = par_a->f->k1;
    off_a->f->k2 = par_a->f->k2;
    off_a->f->k3 = par_a->f->k3;
    off_a->f->k4 = par_a->f->k4;
    off_a->g->k0 = par_a->g->k0;
    off_a->g->k1 = par_a->g->k1;
    off_a->g->k2 = par_a->g->k2;
    off_a->g->k3 = par_a->g->k3;
    off_a->g->k4 = par_a->g->k4;
    off_b->f->k0 = par_b->f->k0;
    off_b->f->k1 = par_b->f->k1;
    off_b->f->k2 = par_b->f->k2;
    off_b->f->k3 = par_b->f->k3;
    off_b->f->k4 = par_b->f->k4;
    off_b->g->k0 = par_b->g->k0;
    off_b->g->k1 = par_b->g->k1;
    off_b->g->k2 = par_b->g->k2;
    off_b->g->k3 = par_b->g->k3;
    off_b->g->k4 = par_b->g->k4;
    if (_a) {
        choice = rand() % 32;
        if ((choice & 0b10000) >> 4) {
            off_a->f->k0 = par_b->f->k0;
            off_b->f->k0 = par_a->f->k0;
        } if ((choice & 0b1000) >> 3) {
            off_a->f->k1 = par_b->f->k1;
            off_b->f->k1 = par_a->f->k1;
        } if ((choice & 0b100) >> 2) {
            off_a->f->k2 = par_b->f->k2;
            off_b->f->k2 = par_a->f->k2;
        } if ((choice & 0b10) >> 1) {
            off_a->f->k3 = par_b->f->k3;
            off_b->f->k3 = par_a->f->k3;
        } if (choice & 0b1) {
            off_a->f->k4 = par_b->f->k4;
            off_b->f->k4 = par_a->f->k4;
        }
    } if (_b) {
        choice = rand() % 32;
        if ((choice & 0b10000) >> 4) {
            off_a->f->k0 = par_b->g->k0;
            off_b->g->k0 = par_a->f->k0;
        } if ((choice & 0b1000) >> 3) {
            off_a->f->k1 = par_b->g->k1;
            off_b->g->k1 = par_a->f->k1;
        } if ((choice & 0b100) >> 2) {
            off_a->f->k2 = par_b->g->k2;
            off_b->g->k2 = par_a->f->k2;
        } if ((choice & 0b10) >> 1) {
            off_a->f->k3 = par_b->g->k3;
            off_b->g->k3 = par_a->f->k3;
        } if (choice & 0b1) {
            off_a->f->k4 = par_b->g->k4;
            off_b->g->k4 = par_a->f->k4;
        }
    } if (_c) {
        choice = rand() % 32;
        if ((choice & 0b10000) >> 4) {
            off_a->g->k0 = par_b->f->k0;
            off_b->f->k0 = par_a->g->k0;
        } if ((choice & 0b1000) >> 3) {
            off_a->g->k1 = par_b->f->k1;
            off_b->f->k1 = par_a->g->k1;
        } if ((choice & 0b100) >> 2) {
            off_a->g->k2 = par_b->f->k2;
            off_b->f->k2 = par_a->g->k2;
        } if ((choice & 0b10) >> 1) {
            off_a->g->k3 = par_b->f->k3;
            off_b->f->k3 = par_a->g->k3;
        } if (choice & 0b1) {
            off_a->g->k4 = par_b->f->k4;
            off_b->f->k4 = par_a->g->k4;
        }
    } if (_d) {
        choice = rand() % 32;
        if ((choice & 0b10000) >> 4) {
            off_a->g->k0 = par_b->g->k0;
            off_b->g->k0 = par_a->g->k0;
        } if ((choice & 0b1000) >> 3) {
            off_a->g->k1 = par_b->g->k1;
            off_b->g->k1 = par_a->g->k1;
        } if ((choice & 0b100) >> 2) {
            off_a->g->k2 = par_b->g->k2;
            off_b->g->k2 = par_a->g->k2;
        } if ((choice & 0b10) >> 1) {
            off_a->g->k3 = par_b->g->k3;
            off_b->g->k3 = par_a->g->k3;
        } if (choice & 0b1) {
            off_a->g->k4 = par_b->g->k4;
            off_b->g->k4 = par_a->g->k4;
        }
    }
}

void crossover_temp(Individual* a, Individual* b) {
    if (size_offspring < max_population) {
        if (new_offspring == NULL){
            limit_offspring = selected;
            new_offspring = (Individual**)malloc(sizeof(Individual*) * limit_offspring);
        }
        if (size_offspring >= limit_offspring - 3) {
            limit_offspring += selected;
            if (limit_offspring > max_population) limit_offspring = max_population;
            Individual** temp_ptr = (Individual**)realloc(new_offspring, 
                sizeof(Individual*) * limit_offspring);
            if (temp_ptr == NULL) { 
                free(new_offspring);
                return;
            } 
            else {
                new_offspring = temp_ptr; 
            }
        }
        Individual* new_a = create_individual(a->f->type, a->g->type);
        Individual* new_b = create_individual(b->f->type, b->g->type);
        *(new_offspring + size_offspring) = new_a;
        size_offspring++;
        *(new_offspring + size_offspring) = new_b;
        size_offspring++;
        if(a->f->type == b->f->type && a->g->type == b->g->type) {
            mix_genes(a, b, new_a, new_b, true, false, false, true);
        } else if (a->f->type == b->g->type && a->g->type == b->f->type) {
            mix_genes(a, b, new_a, new_b, false, true, true, false);
        } else if (a->f->type == b->f->type) {
            mix_genes(a, b, new_a, new_b, true, false, false, false);
        } else if (a->f->type == b->g->type) {
            mix_genes(a, b, new_a, new_b, false, true, false, false);
        } else if (a->g->type == b->f->type) {
            mix_genes(a, b, new_a, new_b, false, false, true, false);
        } else {
            mix_genes(a, b, new_a, new_b, false, false, false, true);
        }
    }
}

void crossover() {
    int size, i = 0, j, to_crossover, choice;
    Individual* temp;
    new_offspring == NULL;
    size_offspring = 0;
    limit_offspring = 0;
    while(i < selected){
        temp = *(selection_ptr + i);
        size = 10;
        crossover_ptr = (Individual**)malloc(sizeof(Individual*) * size);
        j = 0;
        to_crossover = 0;
        while (j < selected) {
            if (j == i) {
                j++;
                continue;
            }
            else if (temp->f->type == (*(selection_ptr + j))->f->type
                    || temp->f->type == (*(selection_ptr + j))->g->type
                    || temp->g->type == (*(selection_ptr + j))->f->type
                    || temp->g->type == (*(selection_ptr + j))->g->type){
                if (selected >= size) {
                    size += 10;
                    Individual** temp_ptr = (Individual**)realloc(crossover_ptr, 
                        sizeof(Individual*) * size);
                    if (temp_ptr == NULL) { 
                        free(crossover_ptr);
                        return;
                    } 
                    else {
                        crossover_ptr = temp_ptr; 
                    }
                }
                *(crossover_ptr + to_crossover) = *(selection_ptr + j);
                to_crossover++;
            }
            j++;
        }
        Individual** temp_ptr = (Individual**)realloc(crossover_ptr, 
            sizeof(Individual*) * to_crossover);
        if (temp_ptr == NULL) { 
            free(crossover_ptr);
            return;
        } 
        else {
            crossover_ptr = temp_ptr; 
        }
        choice = rand() % to_crossover;
        crossover_temp(temp, *(crossover_ptr + choice));
        free(crossover_ptr);
        i++;
    }
    if (new_offspring != NULL) {
        Individual** temp_ptr = (Individual**)realloc(new_offspring, 
            sizeof(Individual*) * size_offspring);
        if (temp_ptr == NULL) { 
            free(new_offspring);
            return;
        } 
        else {
            new_offspring = temp_ptr; 
        }
    }
}

void calc_fitness_offspring() {
    int i = 0;
    while (i < size_offspring) {
        calc_fitness_temp(*(new_offspring + i));
        i++;
    }
}

void mutation_temp(Individual* ind) {
    printf("Generation %d | ID %d mutated!\n", generations, ind->id);
    int choice = rand() % 2;
    int sign = rand() % 2 == 1 ? 1 : -1;
    if (choice == 0) {
        switch (ind->f->type) {
            case '0':
                ind->f->k0 += (float)rand() / (float)(RAND_MAX) * sign;
                break;
            
            default:
                break;
        }
    } else {
        switch (ind->g->type) {
            case '0':
                ind->g->k0 += (float)rand() / (float)(RAND_MAX) * sign;
                break;
            
            default:
                break;
        }
    }
}

void compute_mutations() {
    for (int i = 0; i < size_offspring; i++) {
        if (rand() % max_population < mutation_prob) 
            mutation_temp(*(new_offspring + i));
    }
}

void add_offspring() {
    int i = 0;
    Individual* temp;
    while (i < size_offspring) {
        temp = first_individual;
        first_individual = first_individual->next;
        free(temp->f);
        free(temp->g);
        free(temp);
        i++;
    } 

    for (i = 0; i < size_offspring; i++) {
        if (first_individual == NULL) first_individual = *(new_offspring + i);
        else {
            if(first_individual->fitness < (*(new_offspring + i))->fitness){
                (*(new_offspring + i))->next = first_individual;
                first_individual = *(new_offspring + i);
            } else {
                Individual* prev = first_individual;
                Individual* temp = prev->next;
                while(temp != NULL) {
                    if(temp->fitness < (*(new_offspring + i))->fitness) break;
                    prev = temp;
                    temp = temp->next;
                }
                prev->next = *(new_offspring + i);
                (*(new_offspring + i))->next = temp;
            }
        }
    }

    free(new_offspring);
    free(selection_ptr);
}

void print_population(){
    // Printing the population
    Individual* temp_i = first_individual;
    while (temp_i != NULL){
        printf("%d,%f\n", temp_i->id, temp_i->fitness);
        printf("\t%c,%f,%f,%f,%f,%f\n", temp_i->f->type, 
            temp_i->f->k0, temp_i->f->k1, temp_i->f->k2, temp_i->f->k3, temp_i->f->k4);
        printf("\t%c,%f,%f,%f,%f,%f\n", temp_i->g->type, 
            temp_i->g->k0, temp_i->g->k1, temp_i->g->k2, temp_i->g->k3, temp_i->g->k4);
        temp_i = temp_i->next;
    }
}