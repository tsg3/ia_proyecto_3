#include "../include/population_manager.h"

Function* create_function(char type, float k0, float k1, float k2, float k3, float k4) {
    Function* func = (Function*)malloc(sizeof(Function));
    func->type = type;
    func->k0 = k0;
    func->k1 = k1;
    func->k2 = k2;
    func->k3 = k3;
    func->k4 = k4;
    return func;
}

Individual* create_individual(char type_f, char type_g) {
    Individual* new_individual = (Individual*)malloc(sizeof(Individual));
    new_individual->next = NULL;
    new_individual->id = individuals_created;
    new_individual->fitness = 0;

    Function* new_func;
    float constant, m, k2, k3, k4;
    int bin, order;
    
    switch (type_f) {
        case '0':
            constant = (float)(last_y - first_y) * (2.0 * ((float)rand() / (float)(RAND_MAX)) - 1);
            new_func = create_function('0', constant, 0.0, 0.0, 0.0, 0.0);
            break;

        case '1':
            order = rand() % 4;
            bin = rand() % 2 == 1 ? 1 : -1;
            constant = pow(4.0 * ((float)rand() / (float)(RAND_MAX)), bin);
            m = constant * approx_m;
            switch (order) {
                case 0:
                    new_func = create_function('1', last_y - m * last_x, m, 0.0, 0.0, 0.0);
                    break;

                case 1:
                    k2 = 2 * ((float)rand() / (float)(RAND_MAX)) - 1;
                    new_func = create_function('1', last_y - m * last_x, m, k2, 0.0, 0.0);
                    break;

                case 2:
                    k2 = 2 * ((float)rand() / (float)(RAND_MAX)) - 1;
                    k3 = 2 * ((float)rand() / (float)(RAND_MAX)) - 1;
                    new_func = create_function('1', last_y - m * last_x, m, k2, k3, 0.0);
                    break;

                case 3:
                    k2 = 2 * ((float)rand() / (float)(RAND_MAX)) - 1;
                    k3 = 2 * ((float)rand() / (float)(RAND_MAX)) - 1;
                    k4 = 2 * ((float)rand() / (float)(RAND_MAX)) - 1;
                    new_func = create_function('1', last_y - m * last_x, m, k2, k3, k4);
                    break;

                default:
                    break;
            }
            break;

        case '2':
            bin = rand() % 4;
            constant = log(pow(last_y / 1.0, 1.0 / last_x));
            constant += 0.5 * constant * (2.0 * ((float)rand() / (float)(RAND_MAX)) - 1);
            m = (float)(last_y - first_y) * (((float)rand() / (float)(RAND_MAX)) - 0.5);
            switch (bin) {
                case 1:
                    m *= -1;
                    break;
                
                case 2:
                    m = m * exp(constant * last_y);
                    constant *= -1;
                    break;

                case 3:
                    m = -m * (1 + exp(constant * last_y));
                    constant *= -1;
                    break;

                default:
                    break;
            }
            new_func = create_function('2', m, constant, 0.0, 0.0, 0.0);
            break;

        case '3':
            bin = rand() % 2 == 1 ? 1 : -1;
            m = bin * last_y * ((float)rand() / (float)(RAND_MAX));
            constant = (M_PI / (4 * last_x)) * (79 * ((float)rand() / (float)(RAND_MAX)) + 1);
            new_func = create_function('3', m, constant, 0.0, 0.0, 0.0);
            break;

        case '4':
            bin = rand() % 2 == 1 ? 1 : -1;
            m = bin * last_y * ((float)rand() / (float)(RAND_MAX));
            constant = (M_PI / (4 * last_x)) * (79 * ((float)rand() / (float)(RAND_MAX)) + 1);
            new_func = create_function('4', m, constant, 0.0, 0.0, 0.0);
            break;
        
        default:
            break;
    }
    new_individual->f = new_func;

    switch (type_g) {
        case '0':
            constant = (float)(last_y - first_y) * (2.0 * ((float)rand() / (float)(RAND_MAX)) - 1);
            new_func = create_function('0', constant, 0.0, 0.0, 0.0, 0.0);
            break;

        case '1':
            order = rand() % 4;
            bin = rand() % 2 == 1 ? 1 : -1;
            constant = pow(4.0 * ((float)rand() / (float)(RAND_MAX)), bin);
            m = constant * approx_m;
            switch (order) {
                case 0:
                    new_func = create_function('1', last_y - m * last_x, m, 0.0, 0.0, 0.0);
                    break;

                case 1:
                    k2 = 2 * ((float)rand() / (float)(RAND_MAX)) - 1;
                    new_func = create_function('1', last_y - m * last_x, m, k2, 0.0, 0.0);
                    break;

                case 2:
                    k2 = 2 * ((float)rand() / (float)(RAND_MAX)) - 1;
                    k3 = 2 * ((float)rand() / (float)(RAND_MAX)) - 1;
                    new_func = create_function('1', last_y - m * last_x, m, k2, k3, 0.0);
                    break;

                case 3:
                    k2 = 2 * ((float)rand() / (float)(RAND_MAX)) - 1;
                    k3 = 2 * ((float)rand() / (float)(RAND_MAX)) - 1;
                    k4 = 2 * ((float)rand() / (float)(RAND_MAX)) - 1;
                    new_func = create_function('1', last_y - m * last_x, m, k2, k3, k4);
                    break;

                default:
                    break;
            }
            break;

        case '2':
            bin = rand() % 4;
            constant = log(pow(last_y / 1.0, 1.0 / last_x));
            constant += 0.5 * constant * (2.0 * ((float)rand() / (float)(RAND_MAX)) - 1);
            m = (float)(last_y - first_y) * (((float)rand() / (float)(RAND_MAX)) - 0.5);
            switch (bin) {
                case 1:
                    m *= -1;
                    break;
                
                case 2:
                    m = m * exp(constant * last_y);
                    constant *= -1;
                    break;

                case 3:
                    m = -m * (1 + exp(constant * last_y));
                    constant *= -1;
                    break;

                default:
                    break;
            }
            new_func = create_function('2', m, constant, 0.0, 0.0, 0.0);
            break;

        case '3':
            bin = rand() % 2 == 1 ? 1 : -1;
            m = bin * last_y * ((float)rand() / (float)(RAND_MAX));
            constant = (M_PI / (4 * last_x)) * (79 * ((float)rand() / (float)(RAND_MAX)) + 1);
            new_func = create_function('3', m, constant, 0.0, 0.0, 0.0);
            break;

        case '4':
            bin = rand() % 2 == 1 ? 1 : -1;
            m = bin * last_y * ((float)rand() / (float)(RAND_MAX));
            constant = (M_PI / (4 * last_x)) * (79 * ((float)rand() / (float)(RAND_MAX)) + 1);
            new_func = create_function('4', m, constant, 0.0, 0.0, 0.0);
            break;
        
        default:
            break;
    }
    new_individual->g = new_func;

    calc_fitness_temp(new_individual);

    individuals_created++;
    return new_individual;
}

void init_population(int size) {
    individuals_created = 0;

    for (int i = 0; i < size; i++) {
        char f_id = ((i % 25) / 5) + '0';
        char g_id = (i % 5) + '0';
        Individual* new_individual = create_individual(f_id, g_id);

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

float get_value(Function* func, int x) {
    switch (func->type) {
        case '0':
            return func->k0;
            break;
        
        case '1':
            return func->k4 * pow(x, 4) + func->k3 * pow(x, 3) + func->k2 * pow(x, 2) + func->k1 * x + func->k0;
            break;

        case '2':
            return func->k0 * exp(func->k1 * x);
            break;

        case '3':
            return func->k0 * sin(func->k1 * x);
            break;

        case '4':
            return func->k0 * cos(func->k1 * x);
            break;
        
        default:
            break;
    }
}

float get_difference(Individual* ind) {
    Node* temp = data_start;
    int i = data_start->x;
    float sum = 0;

    while (temp != NULL) {
        sum += (float) pow(temp->fx - get_value(ind->f, i) - get_value(ind->g, i), 2);
        i++;
        temp = temp->next;
    }

    return (float) sqrt(sum);
}

void calc_fitness_temp(Individual* individual) {
    individual->fitness = get_difference(individual);
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
    int max_size = max_population / 4;
    selected = 0;
    selection_ptr = (Individual**)malloc(sizeof(Individual*) * max_size);

    Individual* temp = first_individual;
    float divisor = (highest_fitness - lowest_fitness) / 100;
    int high_temp = highest_fitness;
    int low_temp = lowest_fitness;
    int order_h = 0;
    int order_l = 0;
    while (high_temp != 0 || low_temp != 0) {
        if (high_temp != 0) {
            high_temp /= 10;
            order_h++;
        }
        if (low_temp != 0) {
            low_temp /= 10;
            order_l++;
        }
    }
    int range = order_h - order_l;

    int _rand;
    bool dec;
    while (temp != NULL && selected < max_size) {
        _rand = rand() % 101;
        dec = _rand > 12.5 * (float)range + (temp->fitness - lowest_fitness) / divisor ? true : false; // modificar
        if (dec) {
            *(selection_ptr + selected) = temp;
            selected++;
        }
        temp = temp->next;
    }
    if (selected < max_size) {
        Individual** temp_ptr = (Individual**)realloc(selection_ptr, sizeof(Individual*) * selected);
        if (temp_ptr == NULL) { 
            free(selection_ptr);
            return;
        } 
        else {
            selection_ptr = temp_ptr; 
        }
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

void crossover() {
    int i = 0, j, to_crossover, choice;
    Individual* temp;
    new_offspring = (Individual**)malloc(sizeof(Individual*) * 2 * selected);
    size_offspring = 0;
    limit_offspring = 0;
    while(i < selected){
        temp = *(selection_ptr + i);
        crossover_ptr = (Individual**)malloc(sizeof(Individual*) * (selected - 1));
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
                *(crossover_ptr + to_crossover) = *(selection_ptr + j);
                to_crossover++;
            }
            j++;
        }
        choice = rand() % to_crossover;
        crossover_temp(temp, *(crossover_ptr + choice));
        free(crossover_ptr);
        i++;
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
    int choice = rand() % 2;
    int sign = rand() % 2 == 1 ? 1 : -1;
    if (choice == 0) {
        switch (ind->f->type) {
            case '0':
                ind->f->k0 += (float)rand() / (float)(RAND_MAX) * sign;
                break;

            case '1':
                choice = rand() % 5;
                switch (choice) {
                    case 0:
                        ind->f->k0 += sign * (float)rand() / (float)(RAND_MAX);
                        break;

                    case 1:
                        ind->f->k1 += sign * (float)rand() / (float)(RAND_MAX);
                        break;

                    case 2:
                        ind->f->k2 += 0.5 * sign * (float)rand() / (float)(RAND_MAX);
                        break;

                    case 3:
                        ind->f->k3 += 0.25 * sign * (float)rand() / (float)(RAND_MAX);
                        break;

                    case 4:
                        ind->f->k4 += 0.125 * sign * (float)rand() / (float)(RAND_MAX);
                        break;

                    default:
                        break;
                }
                break;
            
            case '2':
                choice = rand() % 2;
                if (choice == 0) {
                    ind->f->k0 += ind->f->k0 * (((float)rand() / (float)(RAND_MAX)) - 0.5);
                } else {
                    ind->f->k1 += ind->f->k1 * 0.5 * sign * (float)rand() / (float)(RAND_MAX);
                }
                break;

            case '3':
                choice = rand() % 2;
                if (choice == 0) {
                    ind->f->k0 += 2 * sign * (float)rand() / (float)(RAND_MAX);
                } else {
                    ind->f->k1 += sign * 0.05 * (float)rand() / (float)(RAND_MAX);
                }
                break;

            case '4':
                choice = rand() % 2;
                if (choice == 0) {
                    ind->f->k0 += 2 * sign * (float)rand() / (float)(RAND_MAX);
                } else {
                    ind->f->k1 += sign * 0.05 * (float)rand() / (float)(RAND_MAX);
                }
                break;

            default:
                break;
        }
    } else {
        switch (ind->g->type) {
            case '0':
                ind->g->k0 += (float)rand() / (float)(RAND_MAX) * sign;
                break;

            case '1':
                choice = rand() % 5;
                switch (choice) {
                    case 0:
                        ind->g->k0 += sign * (float)rand() / (float)(RAND_MAX);
                        break;

                    case 1:
                        ind->g->k1 += sign * (float)rand() / (float)(RAND_MAX);
                        break;

                    case 2:
                        ind->g->k2 += 0.5 * sign * (float)rand() / (float)(RAND_MAX);
                        break;

                    case 3:
                        ind->g->k3 += 0.25 * sign * (float)rand() / (float)(RAND_MAX);
                        break;

                    case 4:
                        ind->g->k4 += 0.125 * sign * (float)rand() / (float)(RAND_MAX);
                        break;

                    default:
                        break;
                }
                break;
            
            case '2':
                choice = rand() % 2;
                if (choice == 0) {
                    ind->g->k0 += ind->f->k0 * (((float)rand() / (float)(RAND_MAX)) - 0.5);
                } else {
                    ind->g->k1 += ind->f->k1 * 0.5 * sign * (float)rand() / (float)(RAND_MAX);
                }
                break;

            case '3':
                choice = rand() % 2;
                if (choice == 0) {
                    ind->g->k0 += 2 * sign * (float)rand() / (float)(RAND_MAX);
                } else {
                    ind->g->k1 += sign * 0.05 * (float)rand() / (float)(RAND_MAX);
                }
                break;

            case '4':
                choice = rand() % 2;
                if (choice == 0) {
                    ind->g->k0 += 2 * sign * (float)rand() / (float)(RAND_MAX);
                } else {
                    ind->g->k1 += sign * 0.05 * (float)rand() / (float)(RAND_MAX);
                }
                break;
            
            default:
                break;
        }
    }
}

void compute_mutations() {
    for (int i = 0; i < size_offspring; i++) {
        if (max_population * ((float)rand() / (float)(RAND_MAX)) < mutation_prob) 
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