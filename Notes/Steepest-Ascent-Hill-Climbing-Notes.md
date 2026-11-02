# Steepest-Ascent Hill Climbing — Complete Notes

## 1. What is Steepest-Ascent Hill Climbing?

Steepest-Ascent Hill Climbing is a variant of the Hill Climbing local search algorithm.

At every iteration, it:
1. Generates all neighboring states of the current state.
2. Evaluates every neighbor.
3. Selects the neighbor with the highest objective value.
4. Moves to that neighbor only if it is better than the current state.
5. Stops when no neighbor is better.

**The important idea:** it does not move to the first better neighbor. It compares all available neighbors and chooses the best one.

## 2. Simple vs Steepest-Ascent Hill Climbing

| Simple Hill Climbing | Steepest-Ascent Hill Climbing |
|---|---|
| Checks neighbors one by one | Evaluates all neighbors |
| Moves to the first better neighbor | Moves to the best neighbor |
| May stop checking after finding an improvement | Must finish evaluating the neighborhood |
| Choice depends on neighbor order | Choice depends on the best evaluation value |

Both are greedy local search methods. Neither is guaranteed to find the global optimum.

## 3. Important Terms

- **Current state:** the solution we are currently exploring.
- **Neighbor:** a state reachable from the current state in one allowed move.
- **Objective function:** a function that assigns a score to a state.
- **Best neighbor:** the neighbor with the highest score in a maximization problem.
- **Local optimum:** a state whose neighbors are not better, even though a better state may exist elsewhere.

For a minimization problem, the comparison is reversed: choose the neighbor with the lowest cost.

## 4. Objective Function Used in Our Program

Our C implementation uses:

~~~text
f(x) = -(x - 5)^2 + 25
~~~

We want to **maximize** this function.

Some values are:

| x | f(x) |
|---:|---:|
| 2 | 16 |
| 3 | 21 |
| 4 | 24 |
| 5 | 25 |
| 6 | 24 |
| 7 | 21 |

The global maximum is:

~~~text
x = 5
f(5) = 25
~~~

For this one-dimensional example, the neighbors of x are:

~~~text
left  = x - 1
right = x + 1
~~~

## 5. Algorithm

~~~text
STEEPEST-ASCENT-HILL-CLIMBING(start)

current = start

repeat:

    currentValue = evaluate(current)
    bestNeighbor = current
    bestValue = currentValue

    generate all neighbors of current

    for each neighbor:
        neighborValue = evaluate(neighbor)

        if neighborValue > bestValue:
            bestNeighbor = neighbor
            bestValue = neighborValue

    if bestNeighbor == current:
        stop

    current = bestNeighbor

return current
~~~

Notice that we evaluate every neighbor before deciding where to move.

## 6. Dry Run

Suppose the user enters:

~~~text
start = 2
~~~

Objective function:

~~~text
f(x) = -(x - 5)^2 + 25
~~~

### Iteration 1

Current state:

~~~text
x = 2
f(2) = 16
~~~

Evaluate all neighbors:

| Neighbor | Value |
|---:|---:|
| x = 1 | 9 |
| x = 3 | 21 |

The best neighbor is x = 3 because 21 is the highest value.

Move:

~~~text
2 → 3
~~~

### Iteration 2

Current state:

~~~text
x = 3
f(3) = 21
~~~

Evaluate all neighbors:

| Neighbor | Value |
|---:|---:|
| x = 2 | 16 |
| x = 4 | 24 |

The best neighbor is x = 4.

Move:

~~~text
3 → 4
~~~

### Iteration 3

Current state:

~~~text
x = 4
f(4) = 24
~~~

Evaluate all neighbors:

| Neighbor | Value |
|---:|---:|
| x = 3 | 21 |
| x = 5 | 25 |

The best neighbor is x = 5.

Move:

~~~text
4 → 5
~~~

### Iteration 4

Current state:

~~~text
x = 5
f(5) = 25
~~~

Evaluate all neighbors:

| Neighbor | Value |
|---:|---:|
| x = 4 | 24 |
| x = 6 | 24 |

Neither neighbor is better than the current state.

Therefore, stop.

**Final result:**

~~~text
x = 5
f(x) = 25
~~~

## 7. Understanding the Code

The implementation is:

~~~text
Hill-Climbing/steepest_ascent_hill_climbing.c
~~~

### Step 1: Generate neighbors

~~~c
int neighbors[2] = {current - 1, current + 1};
~~~

For this example, every state has two neighbors: one to the left and one to the right.

### Step 2: Initialize the best candidate

~~~c
int bestNeighbor = current;
int bestNeighborValue = currentValue;
~~~

Initially, we assume that staying at the current state is the best option.

### Step 3: Evaluate every neighbor

~~~c
for (int i = 0; i < 2; i++) {
    int neighbor = neighbors[i];
    int neighborValue = objectiveFunction(neighbor);

    if (neighborValue > bestNeighborValue) {
        bestNeighbor = neighbor;
        bestNeighborValue = neighborValue;
    }
}
~~~

The loop checks both neighbors. Whenever it finds a better value, it updates the best candidate.

### Step 4: Decide whether to move

~~~c
if (bestNeighbor == current) {
    break;
}
~~~

If the best candidate is still the current state, no neighbor improves the objective function. The search stops.

Otherwise, we move:

~~~c
current = bestNeighbor;
~~~

## 8. Why Is It Called Steepest-Ascent?

Imagine standing on a hill with several possible directions to move.

- Simple Hill Climbing takes the first direction that goes upward.
- Steepest-Ascent Hill Climbing checks every available direction and chooses the one with the greatest increase in height.

It chooses the steepest available uphill move, not necessarily the path that leads to the global highest peak.

## 9. Limitations

### Local maximum

The algorithm may stop at a local maximum because all immediate neighbors are worse, even if a higher peak exists elsewhere.

### Plateau

If several neighboring states have the same value, the algorithm may have no strictly improving move.

### Ridge

The best route along a narrow ridge may require moves that do not immediately increase the objective value.

### Starting-state dependence

Different starting states can lead to different final states.

### Expensive neighborhoods

If a state has many neighbors, evaluating all of them can take significant time.

## 10. Time and Space Complexity

Let:
- **b** = number of neighbors evaluated per iteration.
- **k** = number of iterations.

If evaluating one neighbor takes O(1):

- Time complexity: **O(k × b)**.
- Auxiliary space: **O(b)** if all neighbors are stored; it can be O(1) if neighbors are generated one at a time.

For our one-dimensional example, b = 2, so each iteration checks exactly two neighbors.

The total number of iterations depends on the starting state and the problem landscape.

## 11. Advantages

1. Easy to understand and implement.
2. Uses little memory.
3. Makes the best immediate move among the current neighbors.
4. Useful for optimization problems with a well-defined neighborhood and objective function.

## 12. Simple vs Steepest-Ascent vs Stochastic

| Variant | How it selects the next state |
|---|---|
| Simple Hill Climbing | First neighbor that improves the current state |
| Steepest-Ascent Hill Climbing | Best among all evaluated neighbors |
| Stochastic Hill Climbing | Randomly selects from improving neighbors |

## 13. Important Exam Points

- Steepest-Ascent Hill Climbing is a **local search** and **greedy optimization** technique.
- It evaluates all neighboring states before selecting the next move.
- For maximization, it selects the neighbor with the highest objective value.
- It stops when no neighbor has a strictly better value.
- It is not guaranteed to find the global optimum.
- It can get stuck at local maxima, plateaus, and ridges.

**One-line answer:** Steepest-Ascent Hill Climbing evaluates all neighbors of the current state and moves to the one with the maximum improvement.

## 14. Compile and Run

From the repository root:

~~~bash
gcc Hill-Climbing/steepest_ascent_hill_climbing.c -o steepest_ascent
./steepest_ascent
~~~

Try starting values such as 2, 4, 5, and 8, and observe how the algorithm moves.

## 15. Learning Progression

~~~text
Basic Hill Climbing
        ↓
Steepest-Ascent Hill Climbing
        ↓
Stochastic Hill Climbing
        ↓
Random-Restart Hill Climbing
        ↓
Best First Search
        ↓
A* Search
~~~
