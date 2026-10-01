# Hill Climbing — Complete Notes

## 1. What is Hill Climbing?

Hill Climbing is a local search and optimization algorithm used in Artificial Intelligence.

The basic idea is:

> Start from a state, examine its neighboring states, move to a better neighbor, and repeat until no better neighbor exists.

It is called Hill Climbing because we can imagine the search as trying to climb toward the highest point of a landscape.

For a maximization problem:

~~~text
Current State
     |
     v
Examine neighbors
     |
     v
Is a better neighbor available?
     |
   Yes ------> Move there
     |
    No
     |
    STOP
~~~

## 2. Why is it a Local Search Algorithm?

Hill Climbing does not normally explore the entire search space.

It focuses on:
- the current state
- its neighboring states
- the best next move

So it makes a local decision at every step.

This makes Hill Climbing memory-efficient, but it also creates an important problem: the algorithm can get stuck at a state that looks best locally but is not globally best.

## 3. State

A state represents one possible solution to the problem.

For our simple example, the state is just x.

For a more complicated AI problem, a state could represent:
- a position on a board
- an arrangement of objects
- a route
- a schedule
- a configuration of parameters

## 4. Objective Function

We need a way to decide whether one state is better than another.

This is done using an objective function.

For our example:

~~~text
f(x) = -(x - 5)^2 + 25
~~~

We want to maximize this function.

| x | f(x) |
|---:|---:|
| 2 | 16 |
| 3 | 21 |
| 4 | 24 |
| 5 | 25 |
| 6 | 24 |
| 7 | 21 |

Therefore:

~~~text
maximum value = 25
x = 5
~~~

## 5. Neighboring States

A neighbor is a state that can be reached using one allowed move.

For our one-dimensional example:

~~~text
left  = x - 1
right = x + 1
~~~

If the current state is x = 4, the neighbors are 3 and 5.

The algorithm compares their objective values with the current value.

# 6. Basic Hill Climbing Algorithm

For a maximization problem:

~~~text
1. Choose an initial state.
2. Evaluate the current state.
3. Generate neighboring states.
4. Find a better neighbor.
5. If a better neighbor exists:
       Move to it.
6. Otherwise:
       Stop.
7. Repeat.
~~~

### Pseudocode

~~~text
HILL-CLIMBING(start)

current = start

while TRUE:

    evaluate current

    generate neighbors

    choose a better neighbor

    if no better neighbor exists:
        return current

    current = better neighbor
~~~

# 7. Example Dry Run

Suppose the starting state is x = 2.

Our objective function is:

~~~text
f(x) = -(x - 5)^2 + 25
~~~

### Step 1

Current:

~~~text
x = 2
f(2) = 16
~~~

Neighbors:

~~~text
x = 1 → f(1) = 9
x = 3 → f(3) = 21
~~~

3 is better, so:

~~~text
2 → 3
~~~

### Step 2

Current:

~~~text
x = 3
f(3) = 21
~~~

Neighbors:

~~~text
x = 2 → 16
x = 4 → 24
~~~

Move:

~~~text
3 → 4
~~~

### Step 3

Current:

~~~text
x = 4
f(4) = 24
~~~

Neighbors:

~~~text
x = 3 → 21
x = 5 → 25
~~~

Move:

~~~text
4 → 5
~~~

### Step 4

Current:

~~~text
x = 5
f(5) = 25
~~~

Neighbors:

~~~text
x = 4 → 24
x = 6 → 24
~~~

Neither is better, so the algorithm stops.

Final answer:

~~~text
x = 5
f(x) = 25
~~~

# 8. Local Maximum

A local maximum is a state that is better than all of its immediate neighbors but is not the best state in the entire search space.

If the algorithm starts near a smaller peak, it may reach that local maximum and stop because every immediate neighbor is worse.

The algorithm cannot see a higher peak far away.

# 9. Global Maximum

The global maximum is the best state in the entire search space.

For our function:

~~~text
f(x) = -(x - 5)^2 + 25
~~~

the global maximum is:

~~~text
x = 5
f(x) = 25
~~~

# 10. Plateau

A plateau is a flat region where several neighboring states have the same or very similar evaluation.

The algorithm may not know which direction to take because moving to a neighboring state does not improve the objective value.

# 11. Ridge

A ridge is a narrow high region where the best direction may require a sequence of moves that are not directly represented by the available neighboring moves.

The algorithm can have difficulty following the ridge toward a higher point.

# 12. Three Important Problems

~~~text
Hill Climbing
     |
     +---- Local Maximum
     |
     +---- Plateau
     |
     +---- Ridge
~~~

These are among the most important limitations of Hill Climbing.

# 13. Code Implementation

The repository implementation is:

~~~text
Hill-Climbing/hill_climbing.c
~~~

The program uses:

~~~text
f(x) = -(x - 5)^2 + 25
~~~

and considers:

~~~text
left  = x - 1
right = x + 1
~~~

At every step it compares f(left), f(current), and f(right), and moves to a better neighbor.

If neither neighbor is better, the algorithm stops.

# 14. Important Code Logic

The central logic is:

~~~text
if left is better:
    move left

else if right is better:
    move right

else:
    stop
~~~

This is the actual Hill Climbing idea.

# 15. Why Does the Algorithm Stop?

The algorithm stops when:

~~~text
f(left) <= f(current)
AND
f(right) <= f(current)
~~~

That means there is no neighboring state with a higher value.

Therefore, according to the information available locally, the current state is a peak.

# 16. Hill Climbing is Greedy

Hill Climbing is a greedy local search algorithm.

At every step it chooses an improvement immediately available from the current state.

It does not maintain a large frontier of unexplored states like BFS.

It also does not systematically explore branches like DFS.

# 17. Hill Climbing vs BFS vs DFS

| Feature | BFS | DFS | Hill Climbing |
|---|---|---|---|
| Main idea | Explore level by level | Explore deeply | Move toward a better state |
| Data structure | Queue | Stack / recursion | Current state + neighbors |
| Uses heuristic? | No | No | Yes / objective function |
| Search type | Uninformed | Uninformed | Local / optimization |
| Keeps large frontier? | Yes | Yes | No |
| Can get stuck at local maximum? | No | Not in this sense | Yes |
| Memory | Can be high | Usually lower than BFS | Very low |
| Main concern | Level exploration | Deep exploration | Local optimum |

# 18. Advantages

### 1. Simple
Easy to understand and implement.

### 2. Low memory usage
It mainly needs the current state and its neighbors.

### 3. Often fast
If a good direction is available, it can quickly reach a good solution.

### 4. Useful for optimization
It can be applied to problems where we want to maximize or minimize an objective function.

# 19. Limitations

### 1. Local Maximum
It can stop at a locally optimal state.

### 2. Plateau
It may have difficulty deciding where to move on a flat region.

### 3. Ridge
The available moves may make it difficult to follow a narrow high region.

### 4. Starting State
Different starting states can lead to different final states.

# 20. Important Exam Point

> Hill Climbing is not guaranteed to find the global optimum.

It generally finds a state that is locally optimal with respect to its neighborhood.

# 21. Variants of Hill Climbing

### Simple Hill Climbing

Move to the first neighbor that improves the current state.

~~~text
Current
   |
Check neighbor
   |
Better?
 /    \
Yes    No
 |      |
Move   Check next
~~~

### Steepest-Ascent Hill Climbing

Check all neighbors and move to the best one.

~~~text
             Neighbor 1
                 |
Current -------- Neighbor 2
                 |
             Neighbor 3

Choose the best neighbor.
~~~

### Stochastic Hill Climbing

Randomly choose among improving neighbors.

### Random-Restart Hill Climbing

Run Hill Climbing multiple times with different starting states.

This helps reduce the chance of repeatedly getting stuck at the same local maximum.

# 22. The Big Picture

~~~text
             Better neighbor?
                  |
             +----+----+
            Yes        No
             |          |
             v          v
          Move        STOP
             |
             v
       Repeat again
~~~

In one sentence:

> Hill Climbing repeatedly moves from the current state to a better neighboring state until no improvement is possible.

# 23. What We Will Add Next

~~~text
Basic Hill Climbing
        ↓
Simple Hill Climbing
        ↓
Steepest-Ascent Hill Climbing
        ↓
Local Maximum problem
        ↓
Random-Restart Hill Climbing
        ↓
Best First Search
        ↓
A*
~~~

This progression makes the transition from basic local search to heuristic search much easier.
