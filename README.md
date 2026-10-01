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
| Hill Climbing | [Hill-Climbing/hill_climbing.c](Hill-Climbing/hill_climbing.c) | [Detailed Notes](Notes/Hill-Climbing-Notes.md) |

### Planned Topics

- Best First Search
- A* Search
- Simulated Annealing
- Genetic Algorithms
- Fuzzy Logic
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

The current implementation demonstrates this idea using:

    f(x) = -(x - 5)^2 + 25

The algorithm starts from a user-provided value of x, compares x - 1 and x + 1, and moves toward the better neighboring state.

See the [Hill Climbing implementation](Hill-Climbing/hill_climbing.c) and [detailed notes](Notes/Hill-Climbing-Notes.md).

## Implementation Approach

The current implementations use:

- C
- Adjacency matrix for graph algorithms
- visited array
- Manually implemented queue for BFS
- Manually implemented stack for iterative DFS
- Recursion for recursive DFS
- Objective function and neighboring states for Hill Climbing
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

Example Hill Climbing run:

    Enter starting value of x: 2
    Current state: x = 2, f(x) = 16
    Current state: x = 3, f(x) = 21
    Current state: x = 4, f(x) = 24
    Current state: x = 5, f(x) = 25

    Hill Climbing stopped at: x = 5
    Maximum value found: f(x) = 25

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

For Hill Climbing, including the objective function, neighbors, dry run, local maximum, plateau, ridge, variants, advantages, limitations, and comparison with BFS/DFS, see:

**[Hill Climbing Detailed Notes](Notes/Hill-Climbing-Notes.md)**

## Contribution / Expansion

As new algorithms are added, each topic should ideally contain its implementation, a short README, and detailed notes.

The aim is to keep the repository useful not only as a **code collection**, but also as a **self-study reference**.

## Author

**Anuja Kumari**

B.Tech CSE
