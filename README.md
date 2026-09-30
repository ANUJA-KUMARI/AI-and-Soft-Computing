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

### Planned Topics

- Best First Search
- A* Search
- Hill Climbing
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

Our implementation uses **recursion**, which internally behaves like a stack.

## Implementation Approach

The current implementations use:

- C
- Adjacency matrix
- visited array
- Manually implemented queue for BFS
- Recursion for DFS
- No graph traversal library

This makes the code suitable for understanding the algorithm at a fundamental level.

## Running the Programs

### BFS

    gcc BFS/bfs.c -o bfs
    ./bfs

### DFS

    gcc DFS/dfs.c -o dfs
    ./dfs

Example input:

    Enter number of vertices: 6
    Enter number of edges: 6
    Enter each edge as: source destination
    0 1
    0 2
    1 3
    1 4
    2 5
    4 5
    Enter starting vertex: 0

The exact traversal order depends on the graph and the order in which neighboring vertices are checked.

## Learning Path

    Understand the concept
            ↓
    Draw a small graph
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

For a complete beginner-friendly explanation of BFS and DFS, including graph terminology, adjacency matrix, visited array, queue implementation, recursion, stack behavior, dry runs, complexity, BFS vs DFS, common mistakes, and applications, see:

**[BFS & DFS Detailed Notes](Notes/BFS-DFS-Notes.md)**

## Contribution / Expansion

As new algorithms are added, each topic should ideally contain its implementation, a short README, and detailed notes.

The aim is to keep the repository useful not only as a code collection, but also as a **self-study reference**.

## Author

**Anuja Kumari**

B.Tech CSE
