#include "../include/population_manager.h"

int main() {
    // Required for random number generation
    srand(time(NULL));

    max_population = 1000; // Size of population
    highest_fitness = -1;
    lowest_fitness = -1;
    selection_ptr = NULL;
    first_individual = NULL;
    last_individual = NULL;
    selection_ptr = NULL;
    crossover_ptr = NULL;
    new_offspring = NULL;
    mutation_prob = max_population / 25;
    life_span = 10;

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
    init_population();

    generations = 0;
    // printf("\n<<< Initial Population >>>\n\n");
    // print_population();
    // This while should continue after finding a good result
    int i = 0;
    bool res;
    // while (generations < 10000) {
    while (lowest_fitness > 12.5) {
        if (highest_fitness - lowest_fitness < 50) {
            // printf("8\n");
            add_diversity();
            i++;
        }
        // printf("1\n");
        grow_up();
        // printf("2\n");
        res = kill_old();
        if (res)
            break;
        if (size_population == 0) {
            re_fill_population();
        }
        // printf("3\n");
        selection();
        // printf("4\n");
        crossover();
        // printf("5\n");
        compute_mutations();
        // printf("6\n");
        calc_fitness_offspring();
        // printf("7\n");
        add_offspring();
        
        highest_fitness = first_individual->fitness;
        lowest_fitness = last_individual->fitness;

        if (generations % 1000 == 0) {
            int count = 0;
            Individual* temp = first_individual;
            while (temp != NULL) {
                if (temp->fitness < lowest_fitness + 50) count++;
                temp = temp->next;
            }
            printf("%d %d %d %d %f %f\n", generations, i, size_population, count, highest_fitness, lowest_fitness);
            if (count < size_population) {
                clean_similar(count);
                re_fill_population();
            }
        }
        generations++;
    }

    if (res) {
        printf("\n<<< Population %d was very old >>>\n\n", generations);
        print_population();
        exit(1);
    } else if (size_population <= 0) {
        printf("\n<<< No population >>>\n");
        exit(1);
    }

    printf("\n<<< Population %d >>>\n\n", generations);
    print_population();

    printf("Times of premature convergence %d\n", i);

    // Free the pointers used
    
    free_list();
    free_individuals();
    return 0;
}