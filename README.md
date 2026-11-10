# AI and Soft Computing

A beginner-friendly collection of **Artificial Intelligence and Soft Computing algorithms implemented from scratch**, with an emphasis on understanding the ideas behind the code rather than simply using libraries.

> **Goal:** Learn the algorithm, understand why it works, trace it by hand, and then implement it yourself.

## Repository Philosophy

This repository is designed as a learning resource for students starting with AI, graph algorithms, and soft computing.

For every algorithm, the goal is to provide:

1. **Concept** — What problem does the algorithm solve?
2. **Intuition** — How should you think about it?
3. **Logic / mathematics** — What is happening internally?
4. **From-scratch implementation** — No ready-made algorithm functions.
5. **Dry run** — Trace the algorithm on a small example.
6. **Complexity** — Time and space analysis.
7. **Practical notes** — Common mistakes and important observations.

## Current Topics

### Graph Traversal

| Algorithm | Implementation | Notes |
|---|---|---|
| Breadth First Search (BFS) | [BFS/bfs.c](BFS/bfs.c) · [Iterative](BFS/bfs_iterative.c) | [Detailed Notes](Notes/BFS-DFS-Notes.md) |
| Depth First Search (DFS) | [DFS/dfs.c](DFS/dfs.c) · [Iterative](DFS/dfs_iterative.c) | [Detailed Notes](Notes/BFS-DFS-Notes.md) |

### Local Search and Optimization

| Algorithm | Implementation | Notes |
|---|---|---|
| Hill Climbing (Basic) | [Hill-Climbing/hill_climbing.c](Hill-Climbing/hill_climbing.c) | [Detailed Notes](Notes/Hill-Climbing-Notes.md) |
| Steepest-Ascent Hill Climbing | [Hill-Climbing/steepest_ascent_hill_climbing.c](Hill-Climbing/steepest_ascent_hill_climbing.c) | [Detailed Notes](Notes/Steepest-Ascent-Hill-Climbing-Notes.md) |
| Basic Genetic Algorithm | [Genetic-Algorithm/genetic_algorithm.c](Genetic-Algorithm/genetic_algorithm.c) | [Detailed Notes](Notes/Genetic-Algorithm-Notes.md) |

### Fuzzy Logic

| Topic | Implementation | Notes |
|---|---|---|
| Triangular Membership Function | [Fuzzy-Membership-Functions/triangular_membership.py](Fuzzy-Membership-Functions/triangular_membership.py) | [Detailed Notes](Notes/Triangular-Membership-Function-Notes.md) |
| Mamdani Fuzzy Inference System | [Fuzzy-Inference-System/mamdani_fis.py](Fuzzy-Inference-System/mamdani_fis.py) | [Detailed Notes](Notes/Mamdani-FIS-Notes.md) |
| Defuzzification (Centroid and MOM) | [Fuzzy-Defuzzification/defuzzification.py](Fuzzy-Defuzzification/defuzzification.py) | [Detailed Notes](Notes/Defuzzification-Notes.md) |

### Heuristic Search

| Algorithm | Implementation | Notes |
|---|---|---|
| AO* (AO-Star) | [AO-Star/ao_star.c](AO-Star/ao_star.c) | [Detailed Notes](Notes/AO-Star-Notes.md) |
| A* Search | [A-Star/a_star.c](A-Star/a_star.c) | [Detailed Notes](Notes/A-Star-Notes.md) |

### Planned Topics

- Best First Search
- Simulated Annealing
- Neural Network fundamentals
- Other AI and Soft Computing techniques

## BFS and DFS

BFS and DFS are two of the most fundamental graph traversal algorithms.

They answer a basic question:

> **How can we systematically visit the vertices of a graph?**

### BFS

**Breadth First Search** explores the graph **level by level**.

It uses a **Queue**: First In → First Out.

### DFS

**Depth First Search** explores **as deeply as possible before backtracking**.

Our implementation includes both **recursive and iterative** versions. The recursive version uses the program's call stack, while the iterative version uses an explicitly implemented stack.

## Hill Climbing

**Hill Climbing** is a local search and optimization technique.

The basic idea is:

> Start from a state, examine its neighbors, move to a better neighbor, and repeat until no better neighbor exists.

The basic implementation demonstrates this idea using:

    f(x) = -(x - 5)^2 + 25

The algorithm starts from a user-provided value of x, compares x - 1 and x + 1, and moves toward the better neighboring state.

See the [basic Hill Climbing implementation](Hill-Climbing/hill_climbing.c), the [Steepest-Ascent implementation](Hill-Climbing/steepest_ascent_hill_climbing.c), and the [detailed notes](Notes/Hill-Climbing-Notes.md) and [Steepest-Ascent notes](Notes/Steepest-Ascent-Hill-Climbing-Notes.md).

## Genetic Algorithm

A **Genetic Algorithm (GA)** is a population-based optimization technique inspired by natural evolution.

The implementation searches for an integer x from 0 to 31 to maximize:

    f(x) = x^2

It represents each candidate solution as a five-bit chromosome and demonstrates:

- Random population initialization
- Fitness evaluation
- Roulette-wheel selection
- Single-point crossover
- Bit-flip mutation
- Replacement and generation tracking

The program tracks the best solution found so far. It does not use elitism, and because the search is stochastic, it is not guaranteed to find the theoretical optimum in every run.

See the [C implementation](Genetic-Algorithm/genetic_algorithm.c), the [algorithm README](Genetic-Algorithm/README.md), and the [detailed notes](Notes/Genetic-Algorithm-Notes.md).

## AO* (AO-Star)

**AO*** is a heuristic search algorithm for **AND-OR graphs**.

Unlike ordinary path-search algorithms, AO* can represent problems where:
- an **OR node** means we can choose one alternative
- an **AND node** means multiple subproblems must all be solved

For a minimization problem:

    OR  → choose the minimum-cost alternative
    AND → combine the costs of all required children

AO* therefore produces a **solution subgraph**, not necessarily one simple path.

See the [AO* implementation](AO-Star/ao_star.c) and [detailed notes](Notes/AO-Star-Notes.md).

## Implementation Approach

The current implementations use:

- C
- Adjacency matrix for graph algorithms
- visited array
- Manually implemented queue for BFS
- Manually implemented stack for iterative DFS
- Recursion for recursive DFS
- Objective functions and neighboring states for basic and Steepest-Ascent Hill Climbing
- Binary chromosomes, roulette-wheel selection, single-point crossover, and bit-flip mutation for Genetic Algorithm
- Triangular fuzzy membership function implemented in Python with piecewise linear calculation
- Defuzzification using Centroid and Mean of Maxima (MOM) methods in Python
- Mamdani Fuzzy Inference System using MIN implication, MAX aggregation, and Centroid defuzzification
- AND-OR nodes, heuristic values, and cost propagation for AO*
- A* pathfinding using a predefined graph, g(n), h(n), f(n), an open set, and parent tracking
- No ready-made traversal or optimization library

This makes the code suitable for understanding the algorithms at a fundamental level.

## Running the Programs

### BFS

    gcc BFS/bfs.c -o bfs
    ./bfs

### DFS

    gcc DFS/dfs.c -o dfs
    ./dfs

### Hill Climbing

    gcc Hill-Climbing/hill_climbing.c -o hill_climbing
    ./hill_climbing

### Genetic Algorithm

    gcc -std=c11 -Wall -Wextra -pedantic Genetic-Algorithm/genetic_algorithm.c -o genetic_algorithm
    ./genetic_algorithm

### Triangular Fuzzy Membership Function

    python Fuzzy-Membership-Functions/triangular_membership.py

### Defuzzification (Centroid and MOM)

    python Fuzzy-Defuzzification/defuzzification.py

### Mamdani Fuzzy Inference System

    python Fuzzy-Inference-System/mamdani_fis.py

### AO*

    gcc AO-Star/ao_star.c -o ao_star
    ./ao_star

### A* Search

    gcc A-Star/a_star.c -o a_star
    ./a_star

Example AO* output:

    AO* estimated solution cost: 10
    Solution graph: 0 1 3 4

## Learning Path

    Understand the concept
            ↓
    Draw a small problem
            ↓
    Identify states and neighbors
            ↓
    Identify the objective / heuristic function
            ↓
    Trace the algorithm manually
            ↓
    Understand every data structure used
            ↓
    Read the implementation
            ↓
    Dry-run the actual code
            ↓
    Modify the code yourself
            ↓
    Solve related problems

Do not treat the implementations as code to memorize. The objective is to understand **why every line exists**.

## Detailed Notes

For BFS and DFS, see:

**[BFS & DFS Detailed Notes](Notes/BFS-DFS-Notes.md)**

For Hill Climbing, see:

**[Hill Climbing Detailed Notes](Notes/Hill-Climbing-Notes.md)**

For the Triangular Fuzzy Membership Function, see:

**[Triangular Membership Function Notes](Notes/Triangular-Membership-Function-Notes.md)**

For Defuzzification using Centroid and Mean of Maxima, see:

**[Defuzzification Notes](Notes/Defuzzification-Notes.md)**

For the Mamdani Fuzzy Inference System, see:

**[Mamdani FIS Notes](Notes/Mamdani-FIS-Notes.md)**

For Genetic Algorithms, including binary encoding, fitness evaluation, roulette-wheel selection, crossover, mutation, a dry run, complexity, and viva questions, see:

**[Genetic Algorithm Notes](Notes/Genetic-Algorithm-Notes.md)**

For AO*, including AND-OR graphs, OR/AND cost calculations, heuristic values, cost backup, solution graphs, comparisons, advantages, and limitations, see:

**[AO* Detailed Notes](Notes/AO-Star-Notes.md)**

For A* Search, including g(n), h(n), f(n), the open set, path reconstruction, a dry run, and viva questions, see:

**[A* Search Notes](Notes/A-Star-Notes.md)**

## Contribution / Expansion

As new algorithms are added, each topic should ideally contain its implementation, a short README, and detailed notes.

The aim is to keep the repository useful not only as a **code collection**, but also as a **self-study reference**.

## Author

**Anuja Kumari**

B.Tech CSE
