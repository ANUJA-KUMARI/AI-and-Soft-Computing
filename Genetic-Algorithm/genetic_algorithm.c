#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define POPULATION_SIZE 6
#define CHROMOSOME_LENGTH 5
#define GENERATIONS 10
#define CROSSOVER_RATE 0.80
#define MUTATION_RATE 0.01

typedef struct {
    int genes[CHROMOSOME_LENGTH];
} Chromosome;

/* Convert a binary chromosome into its decimal value. */
int decode(const Chromosome *chromosome) {
    int value = 0;

    for (int i = 0; i < CHROMOSOME_LENGTH; i++) {
        value = value * 2 + chromosome->genes[i];
    }

    return value;
}

/* Fitness function: maximize f(x) = x * x. */
int calculate_fitness(const Chromosome *chromosome) {
    int x = decode(chromosome);
    return x * x;
}

/* Create a population of random binary chromosomes. */
void initialize_population(Chromosome population[]) {
    for (int i = 0; i < POPULATION_SIZE; i++) {
        for (int j = 0; j < CHROMOSOME_LENGTH; j++) {
            population[i].genes[j] = rand() % 2;
        }
    }
}

/* Select one parent using roulette-wheel selection. */
int select_parent(const Chromosome population[]) {
    int total_fitness = 0;

    for (int i = 0; i < POPULATION_SIZE; i++) {
        total_fitness += calculate_fitness(&population[i]);
    }

    /* If every fitness is zero, choose a parent randomly. */
    if (total_fitness == 0) {
        return rand() % POPULATION_SIZE;
    }

    double pick = ((double) rand() / (double) RAND_MAX) * total_fitness;
    int cumulative_fitness = 0;

    for (int i = 0; i < POPULATION_SIZE; i++) {
        cumulative_fitness += calculate_fitness(&population[i]);

        if (pick <= cumulative_fitness) {
            return i;
        }
    }

    return POPULATION_SIZE - 1;
}

/* Perform single-point crossover to create two children. */
void crossover(const Chromosome *parent1, const Chromosome *parent2,
               Chromosome *child1, Chromosome *child2) {
    double probability = (double) rand() / (double) RAND_MAX;

    if (probability < CROSSOVER_RATE) {
        int point = 1 + rand() % (CHROMOSOME_LENGTH - 1);

        for (int i = 0; i < CHROMOSOME_LENGTH; i++) {
            if (i < point) {
                child1->genes[i] = parent1->genes[i];
                child2->genes[i] = parent2->genes[i];
            } else {
                child1->genes[i] = parent2->genes[i];
                child2->genes[i] = parent1->genes[i];
            }
        }
    } else {
        /* If crossover does not happen, copy the parents. */
        *child1 = *parent1;
        *child2 = *parent2;
    }
}

/* Flip each bit independently with the mutation probability. */
void mutate(Chromosome *chromosome) {
    for (int i = 0; i < CHROMOSOME_LENGTH; i++) {
        double probability = (double) rand() / (double) RAND_MAX;

        if (probability < MUTATION_RATE) {
            chromosome->genes[i] = 1 - chromosome->genes[i];
        }
    }
}

/* Find the index of the fittest chromosome in a population. */
int find_best(const Chromosome population[]) {
    int best_index = 0;

    for (int i = 1; i < POPULATION_SIZE; i++) {
        if (calculate_fitness(&population[i]) >
            calculate_fitness(&population[best_index])) {
            best_index = i;
        }
    }

    return best_index;
}

void print_chromosome(const Chromosome *chromosome) {
    for (int i = 0; i < CHROMOSOME_LENGTH; i++) {
        printf("%d", chromosome->genes[i]);
    }
}

int main(void) {
    Chromosome population[POPULATION_SIZE];
    Chromosome new_population[POPULATION_SIZE];
    Chromosome best_ever;

    /* Seed the random number generator once. */
    srand((unsigned int) time(NULL));

    printf("BASIC GENETIC ALGORITHM\n");
    printf("Objective: Maximize f(x) = x^2, where 0 <= x <= 31\n\n");

    initialize_population(population);

    int best_index = find_best(population);
    best_ever = population[best_index];

    printf("Initial Population:\n");
    for (int i = 0; i < POPULATION_SIZE; i++) {
        printf("Chromosome: ");
        print_chromosome(&population[i]);
        printf(" | x = %2d | Fitness = %3d\n",
               decode(&population[i]), calculate_fitness(&population[i]));
    }

    for (int generation = 1; generation <= GENERATIONS; generation++) {
        int count = 0;

        /* Generate children until the new population is full. */
        while (count < POPULATION_SIZE) {
            int parent1_index = select_parent(population);
            int parent2_index = select_parent(population);
            Chromosome child1, child2;

            crossover(&population[parent1_index], &population[parent2_index],
                      &child1, &child2);

            mutate(&child1);
            mutate(&child2);

            new_population[count++] = child1;

            if (count < POPULATION_SIZE) {
                new_population[count++] = child2;
            }
        }

        /* Replace the old population with the new generation. */
        for (int i = 0; i < POPULATION_SIZE; i++) {
            population[i] = new_population[i];
        }

        best_index = find_best(population);
        if (calculate_fitness(&population[best_index]) >
            calculate_fitness(&best_ever)) {
            best_ever = population[best_index];
        }

        printf("Generation %2d: Best chromosome = ", generation);
        print_chromosome(&population[best_index]);
        printf(" | x = %2d | Fitness = %3d\n",
               decode(&population[best_index]),
               calculate_fitness(&population[best_index]));
    }

    printf("\nBest Solution Found:\n");
    printf("Chromosome: ");
    print_chromosome(&best_ever);
    printf("\nValue of x: %d\n", decode(&best_ever));
    printf("Maximum fitness found: %d\n", calculate_fitness(&best_ever));
    printf("Theoretical maximum: x = 31, fitness = 961\n");

    return 0;
}
