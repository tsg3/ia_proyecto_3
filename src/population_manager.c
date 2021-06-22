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
    new_individual->prev = NULL;
    new_individual->id = individuals_created;
    new_individual->fitness = 0;
    new_individual->age = 1;

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
    size_population++;
    return new_individual;
}

void init_population() {
    individuals_created = 0;
    size_population = 0;

    for (int i = 0; i < max_population; i++) {
        char f_id = ((i % 25) / 5) + '0';
        char g_id = (i % 5) + '0';
        Individual* new_individual = create_individual(f_id, g_id);

        if (first_individual == NULL) {
            first_individual = new_individual;
            last_individual = new_individual;
        }
        else {
            if(first_individual->fitness < new_individual->fitness){
                new_individual->next = first_individual;
                first_individual->prev = new_individual;
                first_individual = new_individual;
            } else if(last_individual->fitness > new_individual->fitness){
                new_individual->prev = last_individual;
                last_individual->next = new_individual;
                last_individual = new_individual;
            } else {
                Individual* prev = first_individual;
                Individual* temp = prev->next;
                while(temp != NULL) {
                    if(temp->fitness < new_individual->fitness) break;
                    prev = temp;
                    temp = temp->next;
                }
                prev->next = new_individual;
                new_individual->prev = prev;
                new_individual->next = temp;
                temp->prev = new_individual;
            }
        }
    }
}

void re_fill_population () {
    int i = 0, necessary = max_population - size_population;
    while (i < necessary) {
        char f_id = ((individuals_created % 25) / 5) + '0';
        char g_id = (individuals_created % 5) + '0';
        Individual* new_individual = create_individual(f_id, g_id);

        if (first_individual == NULL) {
            first_individual = new_individual;
            last_individual = new_individual;
        }
        else {
            if(first_individual->fitness < new_individual->fitness){
                new_individual->next = first_individual;
                first_individual->prev = new_individual;
                first_individual = new_individual;
            } else if(last_individual->fitness > new_individual->fitness){
                new_individual->prev = last_individual;
                last_individual->next = new_individual;
                last_individual = new_individual;
            } else {
                Individual* prev = first_individual;
                Individual* temp = prev->next;
                while(temp != NULL) {
                    if(temp->fitness < new_individual->fitness) break;
                    prev = temp;
                    temp = temp->next;
                }
                prev->next = new_individual;
                new_individual->prev = prev;
                new_individual->next = temp;
                temp->prev = new_individual;
            }
        }
        i++;
    }
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

    return (float) sqrt(sum) / 2.0;
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
    int max_size = max_population / 10;
    selected = 0;
    selection_ptr = (Individual**)malloc(sizeof(Individual*) * max_size);

    Individual* temp = last_individual;
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
        temp = temp->prev;
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
    size_population -= 2;
    individuals_created--;
    *(new_offspring + size_offspring) = new_a;
    size_offspring++;
    // *(new_offspring + size_offspring) = new_b;
    // size_offspring++;
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
    free(new_b->f);
    free(new_b->g);
    free(new_b);
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
        if (to_crossover > 0) {
            choice = rand() % to_crossover;
            crossover_temp(temp, *(crossover_ptr + choice));
        }
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

void mutation_temp(Individual* ind, float scale) {
    int choice = rand() % 2;
    int sign = rand() % 2 == 1 ? 1 : -1;
    if (choice == 0) {
        switch (ind->f->type) {
            case '0':
                ind->f->k0 += (float)rand() / (float)(RAND_MAX) * sign * scale;
                break;

            case '1':
                choice = rand() % 5;
                switch (choice) {
                    case 0:
                        ind->f->k0 += scale * sign * (float)rand() / (float)(RAND_MAX);
                        break;

                    case 1:
                        ind->f->k1 += scale * sign * (float)rand() / (float)(RAND_MAX);
                        break;

                    case 2:
                        ind->f->k2 += scale * 0.5 * sign * (float)rand() / (float)(RAND_MAX);
                        break;

                    case 3:
                        ind->f->k3 += scale * 0.25 * sign * (float)rand() / (float)(RAND_MAX);
                        break;

                    case 4:
                        ind->f->k4 += scale * 0.125 * sign * (float)rand() / (float)(RAND_MAX);
                        break;

                    default:
                        break;
                }
                break;
            
            case '2':
                choice = rand() % 2;
                if (choice == 0) {
                    ind->f->k0 += scale * ind->f->k0 * (((float)rand() / (float)(RAND_MAX)) - 0.5);
                } else {
                    ind->f->k1 += scale * ind->f->k1 * 0.5 * sign * (float)rand() / (float)(RAND_MAX);
                }
                break;

            case '3':
                choice = rand() % 2;
                if (choice == 0) {
                    ind->f->k0 += scale * 2 * sign * (float)rand() / (float)(RAND_MAX);
                } else {
                    ind->f->k1 += scale * sign * 0.05 * (float)rand() / (float)(RAND_MAX);
                }
                break;

            case '4':
                choice = rand() % 2;
                if (choice == 0) {
                    ind->f->k0 += scale * 2 * sign * (float)rand() / (float)(RAND_MAX);
                } else {
                    ind->f->k1 += scale * sign * 0.05 * (float)rand() / (float)(RAND_MAX);
                }
                break;

            default:
                break;
        }
    } else {
        switch (ind->g->type) {
            case '0':
                ind->g->k0 += scale * (float)rand() / (float)(RAND_MAX) * sign * 3;
                break;

            case '1':
                choice = rand() % 5;
                switch (choice) {
                    case 0:
                        ind->g->k0 += scale *  sign * (float)rand() / (float)(RAND_MAX);
                        break;

                    case 1:
                        ind->g->k1 += scale * sign * (float)rand() / (float)(RAND_MAX);
                        break;

                    case 2:
                        ind->g->k2 += scale * 0.5 * sign * (float)rand() / (float)(RAND_MAX);
                        break;

                    case 3:
                        ind->g->k3 += scale * 0.25 * sign * (float)rand() / (float)(RAND_MAX);
                        break;

                    case 4:
                        ind->g->k4 += scale * 0.125 * sign * (float)rand() / (float)(RAND_MAX);
                        break;

                    default:
                        break;
                }
                break;
            
            case '2':
                choice = rand() % 2;
                if (choice == 0) {
                    ind->g->k0 += scale * ind->f->k0 * (((float)rand() / (float)(RAND_MAX)) - 0.5);
                } else {
                    ind->g->k1 += scale * ind->f->k1 * 0.5 * sign * (float)rand() / (float)(RAND_MAX);
                }
                break;

            case '3':
                choice = rand() % 2;
                if (choice == 0) {
                    ind->g->k0 += scale * 2 * sign * (float)rand() / (float)(RAND_MAX);
                } else {
                    ind->g->k1 += scale * sign * 0.05 * (float)rand() / (float)(RAND_MAX);
                }
                break;

            case '4':
                choice = rand() % 2;
                if (choice == 0) {
                    ind->g->k0 += scale * 2 * sign * (float)rand() / (float)(RAND_MAX);
                } else {
                    ind->g->k1 += scale * sign * 0.05 * (float)rand() / (float)(RAND_MAX);
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
            mutation_temp(*(new_offspring + i), 1.0);
    }
}

void add_offspring() {
    int i = 0;
    Individual* temp;

    int space = max_population - size_population;
    if (space - size_offspring < 0) {
        while (i < size_offspring - space) {
            temp = first_individual;
            first_individual = first_individual->next;
            first_individual->prev = NULL;
            free(temp->f);
            free(temp->g);
            free(temp);
            i++;
            size_population--;
        } 
    }

    for (i = 0; i < size_offspring; i++) {
        if (first_individual == NULL) {
            first_individual = *(new_offspring + i);
            last_individual = *(new_offspring + i);
        }
        else {
            if (first_individual->fitness <= (*(new_offspring + i))->fitness){
                (*(new_offspring + i))->next = first_individual;
                first_individual->prev = *(new_offspring + i);
                first_individual = *(new_offspring + i);
                highest_fitness = first_individual->fitness;
            } else if (last_individual->fitness >= (*(new_offspring + i))->fitness){
                (*(new_offspring + i))->prev = last_individual;
                last_individual->next = *(new_offspring + i);
                last_individual = *(new_offspring + i);
                lowest_fitness = last_individual->fitness;
            } else {
                Individual* prev = first_individual;
                Individual* temp = prev->next;
                while(temp != NULL) {
                    if(temp->fitness < (*(new_offspring + i))->fitness) break;
                    prev = temp;
                    temp = temp->next;
                }
                prev->next = *(new_offspring + i);
                (*(new_offspring + i))->prev = prev;
                (*(new_offspring + i))->next = temp;
                temp->prev = *(new_offspring + i);
            }
        }
        size_population++;
    }

    if (size_offspring != 0)
        free(new_offspring);
    free(selection_ptr);
}

void grow_up() {
    Individual* temp_i = first_individual;
    while (temp_i != NULL){
        temp_i->age++;
        temp_i = temp_i->next;
    }
}

float sigmoid (int x) {
    return 1.0 / (1.0 + exp(-0.5 * (x - 10)));
}

bool kill_old () {
    Individual* check = first_individual;
    bool result = true;
    while (check != NULL) {
        if (sigmoid(check->age) <= ((float)rand() / (float)(RAND_MAX))) {
            result = false;
            break;
        }
        check = check->next;
    }
    if (first_individual != NULL && !result) {
        Individual* prev = NULL;
        Individual* temp = first_individual;
        while (temp != NULL) {
            if (sigmoid(temp->age) >= ((float)rand() / (float)(RAND_MAX))) {
                if (prev == NULL) {
                    first_individual = temp->next;
                    if (first_individual == NULL)
                        last_individual = NULL;
                    else
                        first_individual->prev = NULL;
                    free(temp->f);
                    free(temp->g);
                    free(temp);
                    temp = first_individual;
                } else {
                    prev->next = temp->next;
                    if (prev->next != NULL)
                        temp->next->prev = prev;
                    else
                        last_individual = prev;
                    free(temp->f);
                    free(temp->g);
                    free(temp);
                    temp = prev->next;
                }
                size_population--;
                continue;
            }
            prev = temp;
            temp = temp->next;
        }
    }
    return result;
}

void reorder_population() {
    if (last_individual != NULL) {
        if (last_individual->prev != NULL) {
            Individual* last_ordered = last_individual->prev;
            Individual* t_to_order = last_ordered->prev;
            Individual* temp_ordered,* t_to_order_prev;
            while (t_to_order != NULL) {
                temp_ordered = last_individual->prev;
                t_to_order_prev = t_to_order->prev;
                if (t_to_order->fitness >= last_ordered->fitness) {
                    last_ordered = t_to_order;
                } else {
                    while (temp_ordered != t_to_order) {
                        if (t_to_order->fitness <= temp_ordered->fitness) {
                            t_to_order->next = temp_ordered->next;
                            t_to_order->prev = temp_ordered;
                            temp_ordered->next->prev = t_to_order;
                            temp_ordered->next = t_to_order;
                            last_ordered->prev = t_to_order_prev;
                            if (t_to_order == first_individual) {
                                first_individual = last_ordered;
                            } else {
                                t_to_order_prev->next = last_ordered;
                            }
                            break;
                        }
                        temp_ordered = temp_ordered->prev;
                    }
                }
                t_to_order = t_to_order_prev;
            }
        }
    }
    
}

void add_diversity() {
    Individual* temp = first_individual;
    while (temp != NULL) {
        if (temp->next == NULL) break;
        if (((float)rand() / (float)(RAND_MAX)) > 0.5) {
            mutation_temp(temp, 3.0);
            calc_fitness_temp(temp);
        }
        temp = temp->next;
    }
    reorder_population();
}

void clean_similar (int similar) {
    int saved = (max_population / 100) + 1;
    if (similar < saved) return;
    similar = (similar - saved) / saved;
    int temp_similar = 0;
    Individual* temp = last_individual;
    Individual* prev = temp->prev;
    while (temp != NULL && saved > 0) {
        if (temp_similar == 0) {
            saved--;
            temp_similar = similar;
        } else {
            if (prev == NULL) {
                first_individual = temp->next;
                first_individual->prev = NULL;
                free(temp->f);
                free(temp->g);
                free(temp);
            } else {
                prev->next = temp->next;
                temp->next->prev = prev;
                free(temp->f);
                free(temp->g);
                free(temp);
            }
            size_population--;
            temp_similar--;
        }
        temp = prev;
        if (prev != NULL)
            prev = temp->prev;
    }
}

void print_population(){
    // Printing the population
    Individual* temp_i = first_individual;
    while (temp_i != NULL){
        printf("%d,%f,%d\n", temp_i->id, temp_i->fitness, temp_i->age);
        printf("\t%c,%f,%f,%f,%f,%f\n", temp_i->f->type, 
            temp_i->f->k0, temp_i->f->k1, temp_i->f->k2, temp_i->f->k3, temp_i->f->k4);
        printf("\t%c,%f,%f,%f,%f,%f\n", temp_i->g->type, 
            temp_i->g->k0, temp_i->g->k1, temp_i->g->k2, temp_i->g->k3, temp_i->g->k4);
        temp_i = temp_i->next;
    }
}