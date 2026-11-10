# A* Search Algorithm — Detailed Notes

## 1. What is A*?

A* (A-Star) is an informed search algorithm used to find a minimum-cost path from a start node to a goal node in a weighted graph.

It uses three values:

- **g(n):** actual cost from the start node to node n.
- **h(n):** estimated cost from node n to the goal.
- **f(n):** estimated total cost through node n.

The main formula is:

`f(n) = g(n) + h(n)`

A* selects the open node with the smallest f-value.

## 2. Intuition

Think of travelling from your home to a destination:

- g(n) tells you how much distance you have already travelled.
- h(n) estimates how much distance is still left.
- f(n) combines both to estimate the total journey.

A* balances the cost already paid and the estimated cost remaining.

## 3. Predefined graph used in the C program

The graph, heuristic values, start node, and goal node are written directly in the program. No user input is required.

### Graph edges

- 0 — 1 has cost 1
- 0 — 2 has cost 4
- 1 — 3 has cost 2
- 2 — 3 has cost 1
- 3 — 4 has cost 3

### Heuristic values

| Node | h(n) |
|---|---:|
| 0 | 5 |
| 1 | 4 |
| 2 | 2 |
| 3 | 2 |
| 4 | 0 |

- Start node = 0
- Goal node = 4

The graph is undirected. The adjacency matrix stores an edge cost in both directions. A value of 0 means there is no edge between those nodes.

## 4. Data structures used

| Variable | Purpose |
|---|---|
| `graph[MAX][MAX]` | Adjacency matrix storing edge costs |
| `heuristic[]` | Estimated remaining cost for each node |
| `g[]` | Best known actual cost from the start |
| `parent[]` | Previous node, used to rebuild the path |
| `open[]` | Nodes waiting to be explored |
| `start` | Starting node (0) |
| `goal` | Destination node (4) |

## 5. Algorithm steps

1. Initialize the predefined graph and heuristic values.
2. Set every g-value to infinity, except the start node whose g-value is 0.
3. Add the start node to the open set.
4. Select the open node with the smallest f = g + h.
5. If it is the goal, stop.
6. Otherwise, examine its neighbours.
7. If a route through the current node gives a smaller g-value, update g and parent.
8. Continue until the goal is reached or no open node remains.
9. Follow parent links backwards to print the path.

## 6. Dry run

Initially, g(0) = 0. All other g-values are infinity.

| Selected node | g(n) | h(n) | f(n) |
|---|---:|---:|---:|
| 0 | 0 | 5 | 5 |
| 1 | 1 | 4 | 5 |
| 3 (after expanding 1) | 3 | 2 | 5 |
| 2 (after expanding 3) | 4 | 2 | 6 |
| 4 (after expanding 3) | 6 | 0 | 6 |

The algorithm finds the path 0 → 1 → 3 → 4.

Total path cost:

`1 + 2 + 3 = 6`

## 7. Expected output

```text
Start node: 0
Goal node: 4
Shortest path: 0 -> 1 -> 3 -> 4
Total path cost: 6
```

## 8. Time and space complexity

This implementation uses an adjacency matrix and scans all nodes to find the open node with the smallest f-value.

- Selecting a node: O(V) per iteration.
- Checking neighbours: O(V) per expanded node.
- Overall time: O(V²) for this small matrix-based implementation under the usual single-expansion analysis.
- Space: O(V²), mainly for the adjacency matrix.

Here V is the number of vertices.

## 9. Important points and limitations

- A* uses both actual path cost and heuristic estimate.
- A* is not the same as Greedy Best First Search. Greedy Best First Search uses h(n) only; A* uses g(n) + h(n).
- A* finds an optimal path when the heuristic is admissible and the search implementation handles improved paths correctly.
- This program allows a node to be explored again if a cheaper route to it is discovered.
- The graph is predefined to keep the lab implementation simple. To test another graph, edit the adjacency matrix, heuristic array, start, and goal in the source code.
- All edge costs in this example are positive.

## 10. Common viva questions

**Q1. What is A*?**  
A* is an informed search algorithm that finds a minimum-cost path using actual cost and heuristic estimate.

**Q2. What is the evaluation function?**  
f(n) = g(n) + h(n).

**Q3. What is g(n)?**  
The actual cost from the start node to the current node.

**Q4. What is h(n)?**  
The estimated cost from the current node to the goal.

**Q5. What is a heuristic?**  
An estimate that helps guide the search towards the goal.

**Q6. What is the difference between A* and Greedy Best First Search?**  
A* uses g(n) + h(n), while Greedy Best First Search uses only h(n).

**Q7. What happens if the heuristic is zero for every node?**  
A* behaves like Uniform Cost Search.

**Q8. What is the open set?**  
The set of discovered nodes that are waiting to be explored.

**Q9. What is the parent array used for?**  
It stores the previous node so the final path can be reconstructed.

**Q10. Why do we use infinity initially for g-values?**  
It represents that no route from the start has been found yet.

## 11. Compile and run

```bash
gcc A-Star/a_star.c -o a_star
./a_star
```

No input is required. The program runs using the graph defined in the source code.
