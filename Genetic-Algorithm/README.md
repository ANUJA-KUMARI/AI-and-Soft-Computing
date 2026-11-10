# Basic Genetic Algorithm (GA)

A from-scratch C implementation of a basic Genetic Algorithm that searches for a value of **x** in the range 0 to 31 to maximize:

```
f(x) = x^2
```

## Genetic Algorithm stages

1. **Initialization:** Generate a population of random 5-bit chromosomes.
2. **Fitness evaluation:** Decode each chromosome into a decimal value and calculate `x * x`.
3. **Selection:** Use roulette-wheel selection. Higher-fitness chromosomes have a higher probability of becoming parents.
4. **Crossover:** Use single-point crossover with a probability of 0.80.
5. **Mutation:** Flip each bit independently with a probability of 0.01.
6. **Replacement:** The children become the next generation.
7. **Termination:** Repeat for 10 generations and report the best solution found.

## Parameters

| Parameter | Value | Meaning |
|---|---:|---|
| Population size | 6 | Chromosomes in each generation |
| Chromosome length | 5 bits | Represents values from 0 to 31 |
| Generations | 10 | Number of evolutionary iterations |
| Crossover rate | 0.80 | Probability of performing crossover |
| Mutation rate | 0.01 | Probability of mutating each bit |

## Compile and run

Using GCC:

```bash
gcc -std=c11 -Wall -Wextra -pedantic Genetic-Algorithm/genetic_algorithm.c -o genetic_algorithm
./genetic_algorithm
```

On Windows (MinGW):

```powershell
gcc -std=c11 -Wall -Wextra -pedantic Genetic-Algorithm/genetic_algorithm.c -o genetic_algorithm.exe
.\genetic_algorithm.exe
```

The program uses random initialization and genetic operations, so the output can differ between runs. The theoretical optimum is `x = 31`, with fitness `961`, but a run is not guaranteed to reach it within 10 generations.

## Important implementation note

This introductory version does not use elitism. It stores the best solution seen across all generations separately, so the final reported best-so-far solution is not lost even if a later population is weaker.

For the concept, operator explanations, dry run, and complexity discussion, see [Genetic Algorithm Notes](../Notes/Genetic-Algorithm-Notes.md).
