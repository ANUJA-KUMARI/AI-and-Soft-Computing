# Genetic Algorithm (GA) — Detailed Notes

## 1. What is a Genetic Algorithm?

A **Genetic Algorithm (GA)** is a population-based optimization technique inspired by natural evolution. It maintains a group of candidate solutions and repeatedly improves them using selection, crossover, and mutation.

The central idea is **survival of the fittest**: solutions with better fitness are more likely to contribute genetic material to the next generation.

A GA does not usually move from one solution to a single neighboring solution. Instead, it works with a population of possible solutions.

## 2. Problem used in this implementation

The program searches for an integer value of x in the range 0 to 31 that maximizes:

```
f(x) = x^2
```

Since five binary bits can represent 32 values:

- Smallest value: `00000` = 0
- Largest value: `11111` = 31
- Fitness of a chromosome: `x * x`
- Theoretical optimum: x = 31, fitness = 961

This is a maximization problem: a larger fitness value is better.

## 3. Important terminology

| Term | Meaning in this program |
|---|---|
| Population | All six candidate chromosomes in one generation |
| Chromosome | One candidate solution represented by five bits |
| Gene | One bit (0 or 1) in a chromosome |
| Individual | Another name for a chromosome |
| Fitness | The quality score, calculated as x squared |
| Parent | A chromosome selected to reproduce |
| Offspring | A new chromosome produced by crossover |
| Generation | One population in the evolutionary process |

Example chromosome:

```
1 0 1 0 1
```

Its binary value is:

```
(10101)2 = 21
```

Its fitness is:

```
f(21) = 21 * 21 = 441
```

## 4. The six main stages

### Stage 1 — Initialization

The program creates six chromosomes. Each of their five genes is randomly assigned either 0 or 1.

In the code, `rand() % 2` produces either 0 or 1.

The initial population is not chosen using fitness. It is generated randomly to provide starting candidate solutions.

### Stage 2 — Fitness evaluation

The `decode()` function converts the five-bit chromosome into a decimal integer.

The `calculate_fitness()` function evaluates:

```
fitness = x * x
```

Example:

| Chromosome | Decimal x | Fitness x² |
|---|---:|---:|
| 00101 | 5 | 25 |
| 01010 | 10 | 100 |
| 10100 | 20 | 400 |
| 11100 | 28 | 784 |

The chromosome with the highest fitness is the best candidate in that population.

### Stage 3 — Selection (roulette-wheel selection)

Selection chooses parents for reproduction.

In roulette-wheel selection, each chromosome receives a probability proportional to its fitness:

```
P(i) = fitness(i) / sum of all population fitness values
```

Suppose three candidates have fitness values 25, 100, and 375. Their total fitness is 500.

- Candidate 1: 25 / 500 = 0.05 = 5%
- Candidate 2: 100 / 500 = 0.20 = 20%
- Candidate 3: 375 / 500 = 0.75 = 75%

The third candidate is more likely to be selected, but the others still have a chance.

The implementation uses a random number and cumulative fitness to select a parent. If the total fitness is zero, it falls back to random selection to avoid division by zero.

### Stage 4 — Crossover (single-point crossover)

Crossover combines two parents to create two children.

Example:

```
Parent 1:  101|10
Parent 2:  010|01
             ^
       Crossover point
```

After exchanging the parts to the right of the crossover point:

```
Child 1:   10101
Child 2:   01010
```

The crossover point is selected between genes, not at either end of the chromosome.

Crossover is attempted with probability 0.80. If crossover does not occur, the children are copies of their respective parents.

### Stage 5 — Mutation (bit-flip mutation)

Mutation introduces small random changes into chromosomes.

For binary chromosomes, bit-flip mutation means:

- 0 becomes 1
- 1 becomes 0

Example:

```
Before:  10101
After:   10001
             ^
        Bit flipped
```

Each bit is independently considered for mutation with probability 0.01 (1%).

Mutation helps maintain diversity and may introduce solutions that crossover alone would not produce.

### Stage 6 — Replacement and termination

The children fill the new population. Once the new population is complete, it replaces the previous population.

This implementation repeats the process for 10 generations.

It also stores the best chromosome seen so far in `best_ever`. This is best-so-far tracking, not elitism: the best chromosome is not forcibly copied into every next generation.

## 5. Mapping the concepts to C functions

| Function | Responsibility |
|---|---|
| `decode()` | Convert binary chromosome to decimal x |
| `calculate_fitness()` | Calculate x squared |
| `initialize_population()` | Generate random chromosomes |
| `select_parent()` | Select one parent using roulette-wheel selection |
| `crossover()` | Create two children using single-point crossover |
| `mutate()` | Perform bit-flip mutation |
| `find_best()` | Find the fittest chromosome in a population |
| `print_chromosome()` | Display the chromosome |
| `main()` | Coordinate the complete GA process |

## 6. Understanding the important C statements

### Binary decoding

The statement:

```c
value = value * 2 + chromosome->genes[i];
```

builds the binary number from left to right.

For chromosome `10101`:

| Step | Current bit | Calculation | Value |
|---|---:|---|---:|
| 1 | 1 | 0 × 2 + 1 | 1 |
| 2 | 0 | 1 × 2 + 0 | 2 |
| 3 | 1 | 2 × 2 + 1 | 5 |
| 4 | 0 | 5 × 2 + 0 | 10 |
| 5 | 1 | 10 × 2 + 1 | 21 |

### Random probability

```c
(double) rand() / (double) RAND_MAX
```

produces a floating-point value between 0 and 1 (inclusive). It is compared with the crossover or mutation rate.

### Bit flip

```c
chromosome->genes[i] = 1 - chromosome->genes[i];
```

If the bit is 0, it becomes 1. If it is 1, it becomes 0.

### Why use srand(time(NULL))?

```c
srand((unsigned int) time(NULL));
```

seeds the pseudo-random number generator using the current time. This helps produce different random sequences across separate runs.

## 7. Dry-run example of the genetic operators

Assume two selected parents:

```
Parent 1 = 10110  (decimal 22)
Parent 2 = 01100  (decimal 12)
```

Suppose the crossover point is after the second bit:

```
Parent 1 = 10|110
Parent 2 = 01|100

Child 1  = 10|100 = 10100 (decimal 20)
Child 2  = 01|110 = 01110 (decimal 14)
```

Their fitness values before mutation are:

- Child 1: 20² = 400
- Child 2: 14² = 196

If mutation flips the last bit of Child 1:

```
10100 -> 10101
```

Then its decimal value becomes 21 and its fitness becomes:

```
21² = 441
```

This illustrates how crossover recombines existing genes and mutation introduces a new variation.

## 8. Parameters used

| Parameter | Value | Explanation |
|---|---:|---|
| Population size | 6 | Six chromosomes per generation |
| Chromosome length | 5 | Five bits per solution |
| Generations | 10 | Ten evolutionary iterations |
| Crossover rate | 0.80 | 80% chance of crossover |
| Mutation rate | 0.01 | 1% chance per gene |

These are demonstration values, not universal optimal settings. Changing them can change the search behavior.

## 9. Output and important observation

The program prints the initial population, the best chromosome in each generation, and the best solution found over the entire run.

Because the initial population and genetic operations are random, different runs can produce different outputs.

The theoretical optimum is:

```
Chromosome = 11111
x = 31
fitness = 31² = 961
```

However, this basic GA is not guaranteed to find the theoretical optimum in only 10 generations.

The implementation tracks the best solution seen so far, but it does not use elitism. Elitism would explicitly copy one or more of the best chromosomes into the next generation.

## 10. Time and space complexity

Let:

- P = population size
- L = chromosome length
- G = number of generations

For each generation:

- Parent selection scans the population to calculate total fitness: O(P) per parent selection.
- There are O(P) parent selections to create a new population, giving O(P²) total selection work in this straightforward implementation.
- Crossover and mutation process O(L) genes per child, for O(PL) work.
- Finding the best chromosome takes O(P).

Overall time complexity:

```
O(G * (P² + P * L))
```

Space complexity:

```
O(P * L)
```

The two population arrays and the best-so-far chromosome store a constant number of populations, so the asymptotic space complexity is O(P × L).

## 11. Advantages and limitations

### Advantages

- Searches multiple candidate solutions at once.
- Does not require gradient information.
- Selection favors fitter solutions.
- Crossover and mutation introduce variation.
- Can be adapted to many optimization problems.

### Limitations

- Does not guarantee the global optimum.
- Results can vary between runs.
- Performance depends on parameter choices and chromosome representation.
- Fitness evaluation can be expensive for complex problems.
- A basic GA may lose a strong individual without elitism.

## 12. Common viva questions

**Q1. What is a Genetic Algorithm?**  
A population-based optimization algorithm inspired by natural selection and evolution.

**Q2. What is a chromosome?**  
A representation of one candidate solution. Here it is a five-bit binary string.

**Q3. What is a gene?**  
An individual element of a chromosome. Here each gene is either 0 or 1.

**Q4. What is a fitness function?**  
A function that measures the quality of a candidate solution. Here, f(x) = x².

**Q5. What is selection?**  
The process of choosing parents for reproduction based on fitness.

**Q6. What is roulette-wheel selection?**  
A selection method where the probability of choosing an individual is proportional to its fitness.

**Q7. What is crossover?**  
An operation that combines genetic material from two parents to create offspring.

**Q8. What is mutation?**  
A random change in one or more genes. Here it flips a bit.

**Q9. Why is mutation needed?**  
It introduces diversity and helps explore new candidate solutions.

**Q10. Does a Genetic Algorithm always find the global optimum?**  
No. It is a stochastic search method and does not guarantee the global optimum.

**Q11. What is elitism?**  
A strategy that copies the best individual(s) directly into the next generation. This implementation tracks the best-so-far solution but does not use elitism.

**Q12. What is the difference between a generation and a population?**  
A population is the set of candidate solutions at one point in the algorithm. A generation is one iteration in which a new population is produced.

## 13. Compile and run

```bash
gcc -std=c11 -Wall -Wextra -pedantic Genetic-Algorithm/genetic_algorithm.c -o genetic_algorithm
./genetic_algorithm
```

For the implementation, see [Genetic-Algorithm/genetic_algorithm.c](../Genetic-Algorithm/genetic_algorithm.c).
