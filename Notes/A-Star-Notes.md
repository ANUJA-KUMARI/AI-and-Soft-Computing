# A* Search Algorithm — Detailed Notes

## 1. What is A*?

A* (A-Star) is an informed search algorithm used to find a low-cost path from a start node to a goal node in a weighted graph.

It uses two values:

- **g(n):** actual cost from the start node to node n.
- **h(n):** estimated cost from node n to the goal.
- **f(n):** estimated total cost of a path through n.

The main formula is:

\[
f(n) = g(n) + h(n)
\]

A* selects the open node with the smallest f-value.

## 2. Intuition

Think of travelling from your home to a destination:

- g(n) tells you how much distance you have already travelled.
- h(n) estimates how much distance is still left.
- f(n) combines both to estimate the total journey.

A* balances the cost already paid and the estimated cost remaining.

## 3. Data structures used in this program

This beginner-friendly C implementation uses:

| Variable | Purpose |
|---|---|
| `graph[MAX][MAX]` | Adjacency matrix storing edge costs |
| `heuristic[]` | Estimated remaining cost for each node |
| `g[]` | Best known actual cost from the start |
| `parent[]` | Previous node, used to rebuild the path |
| `open[]` | Nodes waiting to be explored |
| `closed[]` | Nodes already explored |

Node numbers start from 0. The graph is undirected, and all edge costs must be positive.

## 4. Algorithm steps

1. Read the number of nodes and edges.
2. Read each edge and its cost.
3. Read the heuristic value of every node.
4. Read the start and goal nodes.
5. Set every g-value to infinity, except the start node whose g-value is 0.
6. Add the start node to the open set.
7. Select the open node with the smallest f = g + h.
8. If it is the goal, stop.
9. Otherwise, examine its neighbours.
10. If a route through the current node gives a smaller g-value, update g and parent.
11. Continue until the goal is reached or no open node remains.
12. Follow parent links backwards to print the path.

## 5. Example input

Consider this undirected graph:

- 0 — 1 has cost 1
- 0 — 2 has cost 4
- 1 — 3 has cost 2
- 2 — 3 has cost 1
- 3 — 4 has cost 3

Heuristic values:

| Node | h(n) |
|---|---:|
| 0 | 5 |
| 1 | 4 |
| 2 | 2 |
| 3 | 2 |
| 4 | 0 |

Start = 0, Goal = 4.

Input:

```text
5
5
0 1 1
0 2 4
1 3 2
2 3 1
3 4 3
5
4
2
2
0
0 4
```

Expected output:

```text
Shortest path: 0 -> 1 -> 3 -> 4
Total path cost: 6
```

## 6. Dry run

Initially, g(0) = 0. All other g-values are infinity.

| Selected node | g(n) | h(n) | f(n) |
|---|---:|---:|---:|
| 0 | 0 | 5 | 5 |
| 1 | 1 | 4 | 5 |
| 2 | 4 | 2 | 6 |
| 3 (after expanding 1) | 3 | 2 | 5 |
| 4 (after expanding 3) | 6 | 0 | 6 |

The algorithm chooses node 1, then node 3, and then reaches node 4. The resulting path is 0 → 1 → 3 → 4, with total cost 1 + 2 + 3 = 6.

## 7. Time and space complexity

This implementation uses an adjacency matrix and scans all nodes to find the open node with the smallest f-value.

- Selecting a node: O(V) per iteration.
- Checking neighbours: O(V) per expanded node.
- Overall time: O(V²) for this matrix-based implementation.
- Space: O(V²), mainly for the adjacency matrix.

Here V is the number of vertices.

## 8. Important points and limitations

- A* uses both actual path cost and heuristic estimate.
- A* is not the same as Greedy Best First Search. Greedy Best First Search uses h(n) only; A* uses g(n) + h(n).
- A* gives an optimal path when the heuristic is admissible (it never overestimates the true remaining cost) and the graph/search implementation satisfies the required conditions.
- This program allows a node to be explored again if a cheaper route to it is discovered.
- The example uses small integer costs and a simple adjacency matrix to keep the implementation easy to understand.
- For an undirected graph, each input edge is stored in both directions.

## 9. Common viva questions

**Q1. What is A*?**  
A* is an informed search algorithm that finds a minimum-cost path using actual cost and heuristic estimate.

**Q2. What is the evaluation function?**  
f(n) = g(n) + h(n).

**Q3. What is g(n)?**  
The actual cost from the start node to the current node.

**Q4. What is h(n)?**  
The estimated cost from the current node to the goal.

**Q5. What is a heuristic?**  
A rule or estimate that helps guide the search towards the goal.

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

## 10. Compile and run

```bash
gcc A-Star/a_star.c -o a_star
./a_star
```
