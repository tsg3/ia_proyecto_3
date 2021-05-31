#include "../include/population_manager.h"

int main() {
    // Required for random number generation
    srand(time(NULL));

    max_population = 100; // Size of population
    min = 0; // Start data
    highest_fitness = -1;
    lowest_fitness = -1;
    selection_ptr = NULL;

    // Load function data
    if(load_data() != 0) {
        return -1;
    }

    // Printing the data
    // Node* temp = data_start;
    // while (temp != NULL){
    //     printf("%d,%d\n", temp->x, temp->fx);
    //     temp = temp->next;
    // }

    // Initialize the population
    init_population(max_population);

    // Compute fitness of population
    calc_fitness_all();

    // Printing the population
    // Individual* temp_i = first_individual;
    // while (temp_i != NULL){
    //     printf("%d,%f\n", temp_i->id, temp_i->fitness);
    //     printf("\t%c,%f,%f,%f,%f,%f\n", temp_i->f->type, 
    //         temp_i->f->k0, temp_i->f->k1, temp_i->f->k2, temp_i->f->k3, temp_i->f->k4);
    //     printf("\t%c,%f,%f,%f,%f,%f\n", temp_i->g->type, 
    //         temp_i->g->k0, temp_i->g->k1, temp_i->g->k2, temp_i->g->k3, temp_i->g->k4);
    //     temp_i = temp_i->next;
    // }

    int generations = 0;
    // This while should continue after finding a good result
    while (generations < 1) {
        generations++;
        selection();
    }

    // Free the pointers used
    if (selection_ptr != NULL) {
        free(selection_ptr);
    }
    free_list();
    free_individuals();
    return 0;
}