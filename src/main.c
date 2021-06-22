#include "../include/population_manager.h"

int main() {
    // Required for random number generation
    srand(time(NULL));

    max_population = 100; // Size of population
    highest_fitness = -1;
    lowest_fitness = -1;
    selection_ptr = NULL;
    first_individual = NULL;
    last_individual = NULL;
    selection_ptr = NULL;
    crossover_ptr = NULL;
    new_offspring = NULL;
    mutation_prob = max_population / 25;
    // life_span = 50;

    // Load function data
    if(load_data() != 0) {
        return -1;
    }

    first_x = data_start->x;
    first_y = data_start->fx;
    Node* temp = data_start;
    while (temp->next != NULL) temp = temp->next;
    last_x = temp->x;
    last_y = temp->fx;
    approx_m = (last_y - first_y) / (last_x - first_x);

    // Printing the data
    // Node* temp = data_start;
    // while (temp != NULL){
    //     printf("%d,%d\n", temp->x, temp->fx);
    //     temp = temp->next;
    // }

    // Initialize the population with fitness computing
    init_population(max_population);

    generations = 0;
    printf("\n<<< Initial Population >>>\n\n");
    print_population();
    // This while should continue after finding a good result
    int i = 0;
    while (generations < 0) {
    // while (lowest_fitness > 33.0) {
        if (highest_fitness - lowest_fitness < 50) {
            add_diversity();
            i++;
        }
        grow_up();
        // kill_old();
        selection();
        crossover();
        compute_mutations();
        calc_fitness_offspring();
        add_offspring();
        
        highest_fitness = first_individual->fitness;
        lowest_fitness = last_individual->fitness;

        if (generations % 1000 == 0) printf("%d %f\n", generations, lowest_fitness);
        generations++;
    }

    printf("\n<<< Population %d >>>\n\n", generations);
    print_population();

    printf("%d\n", i);

    // Free the pointers used
    
    free_list();
    free_individuals();
    return 0;
}