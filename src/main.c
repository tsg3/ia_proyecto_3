#include "../include/population_manager.h"

int main() {
    // Required for random number generation
    srand(time(NULL));

    max_population = 100; // Size of population
    min = 0; // Start data
    highest_fitness = -1;
    lowest_fitness = -1;
    selection_ptr = NULL;
    first_individual = NULL;
    selection_ptr = NULL;
    crossover_ptr = NULL;
    new_offspring = NULL;
    mutation_prob = 1;

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

    // Initialize the population with fitness computing
    init_population(max_population);

    generations = 0;
    // This while should continue after finding a good result
    while (generations < 1) {
        selection();
        crossover();
        calc_fitness_offspring();
        compute_mutations();
        add_offspring();
        generations++;
    }

    printf("<<< Population %d >>>\n", generations);
    print_population();

    // Free the pointers used
    
    free_list();
    free_individuals();
    return 0;
}