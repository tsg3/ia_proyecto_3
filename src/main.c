#include "../include/population_manager.h"
#include <ctype.h>

int main(int argc, char* argv[]) {

    if (argc != 4) {
        printf("Error! Correct syntax: <binary_file> <L> <N> <F>\n");
        printf("\tL: Max population size.\n\tN: Number of populations.\n\tF: Fitness required to finish.\n");
        exit(1);
    }

    bool is_digit = true;
    for (int i = 1; i < 4; i++) {
        for (int j = 0; j < strlen((*(argv + i))); j++) {
            if (!isdigit((*(argv + i))[j]) && i != 3) {
                is_digit = false;
                break;
            }
            if (!isdigit((*(argv + i))[j]) && (*(argv + i))[j] != '.' && i == 3) {
                is_digit = false;
                break;
            }
        }
    }
    if (!is_digit) {
        printf("Error! 'L' and 'N' must be integers!\n");
        exit(1);
    }
    
    int L = atoi(*(argv + 1));
    int N = atoi(*(argv + 2));
    float F = atof(*(argv + 3));

    // Required for random number generation
    srand(time(NULL));

    max_population = L; // Size of population
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

    int n = 1;
    while (n < N + 1) {
        printf("\n<<< Executing Population %d >>>\n\n", n);

        // Initialize the population with fitness computing
        highest_fitness = -1;
        lowest_fitness = -1;
        generations = 0;
        init_population();

        // This while should continue after finding a good result
        int i = 0;
        bool res = false;

        // iteration system
        char iters[5];
        bool finish = false;
        while (finish == false) {
            printf("Indique la cantidad de iteraciones que desea ejecutar: ");

            scanf("%s", iters);
            if (strcmp(iters, "x") == 0) break;

            int j = 0;
            int n = atoi(iters);
            while (lowest_fitness > F && j < n) {
                if (highest_fitness - lowest_fitness < 50) {
                    add_diversity();
                    i++;
                }
                grow_up();
                res = kill_old();
                if (res) {
                    finish = true;
                    break;
                }
                if (size_population == 0) {
                    re_fill_population();
                }
                selection();
                crossover();
                compute_mutations();
                calc_fitness_offspring();
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
                    if (count < size_population) {
                        clean_similar(count);
                        re_fill_population();
                    }
                }
                generations++;
                j++;
            }

            if (lowest_fitness <= F) finish = true;

            printf("\n<<< Iterations completed! >>>\n\n");
            print_best();
        }

        if (res && size_population > 0) {
            printf("\n<<< Generation %d was very old >>>\n\n", generations);
            print_best();
            free_individuals();
            free_list();
            exit(1);
        } else if (size_population <= 0) {
            printf("\n<<< No population >>>\n");
            free_individuals();
            free_list();
            exit(1);
        }

        printf("\n<<< Program finished! Last generation was generation %d >>>\n\n", generations);
        print_best();

        printf("Times of premature convergence %d\n", i);

        // Free the individuals list
        free_individuals();

        n++;
    }

    // Free the data list
    free_list();

    return 0;
}