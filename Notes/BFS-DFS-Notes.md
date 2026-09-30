# BFS and DFS — Detailed Beginner Notes

## 1. Why Do We Need Graph Traversal?

A **graph** is a data structure used to represent relationships between objects.

A graph contains:

- **Vertices (nodes)** — the objects
- **Edges** — the connections between objects

For example:

    0 ---- 1
    |      |
    |      |
    2 ---- 3

Here the vertices are 0, 1, 2, and 3. The lines represent edges.

Graphs can represent cities connected by roads, computers connected in a network, people connected through friendships, web pages connected by links, or states in an AI search problem.

## 2. What Is Graph Traversal?

Suppose we start at vertex 0. We need a systematic method for visiting other vertices without repeatedly processing the same vertex.

A **graph traversal algorithm** determines the order in which vertices are visited.

The two fundamental traversal techniques are:

1. **BFS — Breadth First Search**
2. **DFS — Depth First Search**

BFS and DFS can operate on the same graph. The difference is the strategy used to decide which discovered vertex should be explored next.

## 3. Important Graph Terminology

### Vertex

A vertex is a node in the graph.

### Edge

An edge connects two vertices.

    0 ---- 1

The connection between 0 and 1 is an edge.

### Neighbor

If two vertices are directly connected, they are neighbors.

### Degree

For an undirected graph, the degree of a vertex is the number of edges connected to it.

For example:

        1
        |
    2---0---3

Vertex 0 has degree 3.

## 4. Directed vs Undirected Graph

### Undirected Graph

An edge works in both directions.

    0 ---- 1

We can travel from 0 to 1 and from 1 to 0.

That is why the current C implementation uses:

    graph[u][v] = 1;
    graph[v][u] = 1;

### Directed Graph

An edge has a direction.

    0 ----> 1

We can travel from 0 to 1, but not necessarily from 1 to 0.

For a directed graph, we would normally only set graph[u][v] = 1.

## 5. How Do We Store a Graph?

Two common representations are:

1. Adjacency Matrix
2. Adjacency List

The current BFS and DFS programs use an **adjacency matrix** because it makes the underlying idea easy to visualize.

## 6. Adjacency Matrix

Suppose we have:

    0 ---- 1
    |      |
    |      |
    2 ---- 3

The matrix is:

        0  1  2  3
      +------------
    0 | 0  1  1  0
    1 | 1  0  0  1
    2 | 1  0  0  1
    3 | 0  1  1  0

graph[0][1] = 1 means there is an edge between 0 and 1.

graph[0][3] = 0 means there is no direct edge between 0 and 3.

For an undirected graph, the matrix is symmetric because an edge works in both directions.

## 7. Why Do We Need visited[]?

This is one of the most important ideas in BFS and DFS.

Consider a cycle:

    0 ---- 1
    |      |
    |      |
    3 ---- 2

Without remembering which vertices have already been visited, traversal could repeatedly move around the cycle.

Therefore we maintain:

    int visited[MAX_VERTICES] = {0};

Initially every value is 0:

    visited = [0, 0, 0, 0]

When vertex 0 is visited:

    visited = [1, 0, 0, 0]

A value of 0 means not visited and 1 means visited.

The visited array prevents repeated processing and infinite traversal in cyclic graphs.

# 8. BFS — Breadth First Search

## Core Idea

BFS explores the graph **level by level**.

Consider:

            0
           / \
          1   2
         / \   \
        3   4   5

Starting from 0:

    Level 0: 0
    Level 1: 1, 2
    Level 2: 3, 4, 5

BFS visits all vertices at the current distance before moving farther away.

## 9. Why Does BFS Need a Queue?

BFS needs this behavior:

> The vertex discovered first should be processed first.

That is exactly what a **Queue** provides.

A queue follows:

    FIFO = First In, First Out

If we enqueue 1, 2, and 3, then dequeue operations return 1, then 2, then 3.

This is what creates BFS's level-by-level behavior.

## 10. Implementing a Queue From Scratch

Instead of using a queue library, our program creates one:

    typedef struct {
        int items[MAX_VERTICES];
        int front;
        int rear;
    } Queue;

The queue contains:

- items — the storage array
- front — where the next element will be removed
- rear — where the next element will be inserted

Initially:

    q->front = 0;
    q->rear = -1;

This represents an empty queue.

## 11. enqueue()

The purpose of enqueue is to insert an element.

The implementation increases rear and stores the value there.

Suppose rear is -1 and we enqueue 5.

After increasing rear:

    rear = 0

Then:

    items[0] = 5

The queue contains 5.

If we enqueue 7, it becomes:

    [5, 7]

## 12. dequeue()

Dequeue removes the element at the front.

Suppose:

    items = [5, 7, 9]
    front = 0
    rear = 2

The first dequeue returns 5 and increases front to 1.

The logical queue is now:

    [7, 9]

The old value 5 can physically remain in the array; front tells us that it is no longer part of the active queue.

## 13. isEmpty()

Our implementation checks whether:

    rear < front

For example:

    front = 3
    rear = 2

Since 2 is less than 3, the queue is empty.

## 14. BFS Algorithm

The basic algorithm is:

    1. Create visited array.
    2. Create an empty queue.
    3. Mark the starting vertex visited.
    4. Put the starting vertex into the queue.
    5. While the queue is not empty:
       a. Remove the front vertex.
       b. Process it.
       c. Find all unvisited neighbors.
       d. Mark each neighbor visited.
       e. Put each neighbor into the queue.

The order of steps d and e is important. We mark a vertex visited when we discover and enqueue it.

## 15. BFS Code Logic

The initialization is:

    visited[start] = 1;
    enqueue(&q, start);

Then:

    while (!isEmpty(&q))

means continue while there are vertices waiting to be processed.

We remove the next vertex:

    int current = dequeue(&q);

Then process it.

Next we inspect every possible neighbor. With an adjacency matrix, the program checks every column in the current row.

This condition:

    graph[current][next] && !visited[next]

means:

> There is an edge from current to next AND next has not been visited.

Then we do:

    visited[next] = 1;
    enqueue(&q, next);

## 16. BFS Dry Run

Consider:

            0
           / \
          1   2
         / \   \
        3   4   5

Start at 0.

### Step 1

Visit 0.

    visited = [1,0,0,0,0,0]
    queue = [0]

Remove 0. Its unvisited neighbors are 1 and 2.

    queue = [1,2]

Traversal:

    0

### Step 2

Remove 1.

Its neighbors are 0, 3, and 4. Vertex 0 is already visited, so add 3 and 4.

    queue = [2,3,4]

Traversal:

    0 1

### Step 3

Remove 2.

Its unvisited neighbor is 5.

    queue = [3,4,5]

Traversal:

    0 1 2

### Step 4

Remove 3. No new vertices.

### Step 5

Remove 4. No new vertices.

### Step 6

Remove 5. No new vertices.

Final traversal:

    0 1 2 3 4 5

# 17. DFS — Depth First Search

## Core Idea

DFS uses a different strategy:

> Go as deeply as possible before backtracking.

Imagine exploring a maze. You choose a path and continue along it. When you reach a dead end, you return to the previous decision point and try another path.

## 18. Why Does DFS Use a Stack?

DFS naturally follows:

    LIFO = Last In, First Out

This is the behavior of a stack.

Our implementation does not explicitly create a stack. Instead it uses **recursion**.

Every recursive function call is stored in the program's call stack.

Therefore:

    DFS recursion ≈ stack behavior

## 19. DFS Recursive Function

The DFS function receives:

- graph
- number of vertices
- current vertex
- visited array

The first step is:

    visited[current] = 1;

Then the current vertex is processed.

The program checks every possible neighbor. If a neighbor exists and has not been visited, it recursively calls DFS on that neighbor.

The key statement is conceptually:

    dfs(graph, vertices, next, visited);

This means:

> Pause the current DFS call and go deeper into next.

## 20. DFS Dry Run

Using the same graph:

            0
           / \
          1   2
         / \   \
        3   4   5

Start at 0.

Call DFS on 0 and visit 0.

The first unvisited neighbor is 1, so call DFS on 1.

At 1, the first unvisited neighbor is 3, so call DFS on 3.

At 3 there are no new vertices, so return to 1.

Next unvisited neighbor of 1 is 4. Visit 4 and return.

Return to 0. The next unvisited neighbor is 2.

Visit 2, then visit 5.

One valid traversal for this neighbor ordering is:

    0 1 3 4 2 5

## 21. Understanding Backtracking

Backtracking is central to DFS.

Suppose DFS follows:

    0 → 1 → 3

If 3 has no unvisited neighbor, DFS returns:

    3 → 1

Then it checks whether 1 has another unvisited neighbor.

If not, it returns again:

    1 → 0

This returning through recursive calls is the backtracking behavior.

## 22. BFS vs DFS

| Feature | BFS | DFS |
|---|---|---|
| Full form | Breadth First Search | Depth First Search |
| Strategy | Level by level | Go deep first |
| Main structure | Queue | Stack / recursion |
| Order | FIFO | LIFO |
| Backtracking | Not explicit | Natural through recursion |
| Shortest path in unweighted graph | Yes | Not generally |
| Typical uses | Levels, unweighted shortest paths | Backtracking, components, cycle detection |

## 23. Traversal Order Is Not Always Unique

A common beginner mistake is thinking that BFS or DFS always has one fixed output.

Consider:

    0
   / \
  1   2

One BFS order can be:

    0 1 2

If neighbors are examined in the opposite order, another valid order is:

    0 2 1

The same idea applies to DFS.

Traversal order depends on the order in which neighboring vertices are examined.

Our adjacency matrix checks neighbors from index 0 upward, so smaller-numbered neighbors are processed first.

## 24. Time Complexity With Our Adjacency Matrix

Our implementation checks every possible neighbor for each visited vertex.

Therefore, with an adjacency matrix:

    Time Complexity = O(V²)

where V is the number of vertices.

The adjacency matrix itself requires:

    O(V²)

space.

## 25. Adjacency List Complexity

If the graph were represented using an adjacency list, BFS and DFS are commonly:

    O(V + E)

where:

- V = number of vertices
- E = number of edges

This is especially useful for sparse graphs.

The current implementation intentionally uses an adjacency matrix because it is easy for beginners to visualize.

## 26. Space Complexity

For our implementation:

- Graph matrix: O(V²)
- visited array: O(V)
- BFS queue: O(V)
- DFS recursion stack: O(V) in the worst case

The adjacency matrix is therefore the dominant space requirement for large V.

## 27. Why Do We Mark visited Before Enqueueing?

Consider:

    0
   / \
  1---2

Starting at 0, both 1 and 2 can discover the other vertex.

If a vertex were marked only when removed from the queue, it could be inserted multiple times.

Therefore BFS marks it immediately when discovered:

    visited[next] = 1;
    enqueue(&q, next);

This prevents duplicate insertion.

## 28. Common Beginner Mistakes

### Mistake 1 — Forgetting visited[]

This can cause infinite recursion in DFS when cycles exist.

### Mistake 2 — Marking visited too late

For BFS, mark a vertex when it is discovered and enqueued.

### Mistake 3 — Confusing BFS and DFS

Remember:

    BFS → Queue → FIFO → Level-wise
    DFS → Stack/Recursion → LIFO → Depth-wise

### Mistake 4 — Thinking DFS guarantees the shortest path

DFS can find a path, but it does not generally guarantee the shortest path in an unweighted graph.

### Mistake 5 — Assuming traversal order is unique

Neighbor ordering affects the output order.

## 29. Why Is BFS Useful for Shortest Path?

When every edge has equal cost, BFS explores vertices by distance from the source:

    distance 0
        ↓
    distance 1
        ↓
    distance 2
        ↓
    distance 3

Therefore, the first time BFS reaches a vertex, it has reached it using the minimum number of edges.

This makes BFS useful for:

- Shortest path in unweighted graphs
- Minimum number of moves
- Grid problems
- Level-order traversal
- Social-network distance
- State-space search

## 30. Why Is DFS Useful?

DFS is useful when we want to explore entire branches.

Applications include:

- Cycle detection
- Connected components
- Topological sorting
- Maze solving
- Backtracking
- Path exploration
- State-space search
- Bridges and articulation points

## 31. The Most Important Mental Model

### BFS

Think:

    QUEUE
    FIFO
    LEVEL BY LEVEL

Example:

    START
    /   \
   A     B
  / \   / \
 C   D E   F

BFS completes START, then A and B, then C, D, E, and F.

### DFS

Think:

    STACK
    LIFO
    DEPTH FIRST
    BACKTRACK

It goes down one branch as far as possible, then returns to an earlier decision point.

## 32. BFS Pseudocode

    BFS(graph, start):

        create visited array
        create empty queue

        visited[start] = true
        enqueue(start)

        while queue is not empty:

            current = dequeue()
            process current

            for every neighbor of current:

                if neighbor is not visited:
                    mark neighbor visited
                    enqueue neighbor

## 33. DFS Pseudocode

    DFS(graph, current):

        mark current visited
        process current

        for every neighbor:

            if neighbor is not visited:
                DFS(graph, neighbor)

The traversal logic is short. The rest of the C program mainly handles input, graph representation, validation, and the queue implementation.

## 34. How to Study These Implementations

Do not memorize the code.

Instead, draw these four things on paper:

    1. Graph
    2. visited array
    3. Queue for BFS
    4. Call stack for DFS

For BFS, track:

    Queue:
    [ ]

    Visited:
    [ ]

    Current:

For DFS, track the recursive calls:

    DFS(0)
      DFS(1)
        DFS(3)

This makes the algorithms much easier to understand than simply reading the source code.

## 35. Experiments to Try

### Experiment 1

Change the starting vertex.

### Experiment 2

Change the order of edges.

### Experiment 3

Create a cycle and observe why visited is necessary.

### Experiment 4

Create a disconnected graph such as:

    0 -- 1       4 -- 5

Start from 0 and notice that single-source traversal visits only the component containing 0.

### Experiment 5

Modify the program to traverse all connected components.

This is a very useful next step.

## 36. Natural Next Steps

After BFS:

    BFS
     ↓
    Shortest Path in Unweighted Graph
     ↓
    Connected Components
     ↓
    Cycle Detection
     ↓
    BFS on Grids

After DFS:

    DFS
     ↓
    Recursion
     ↓
    Backtracking
     ↓
    Connected Components
     ↓
    Cycle Detection
     ↓
    Topological Sort
     ↓
    Bridges / Articulation Points

After these fundamentals, AI search algorithms become easier to understand:

    BFS
     ↓
    Best First Search
     ↓
    A* Search

They all involve maintaining a frontier of states that still need to be explored, but they choose the next state using different rules.

## 37. Final Summary

The entire topic can be remembered using two lines:

    BFS = Queue + Visited + Level-by-Level Exploration

    DFS = Recursion/Stack + Visited + Depth-First Exploration

The most important concepts are:

1. What a graph is.
2. How the graph is represented.
3. Why visited is required.
4. Why BFS needs a queue.
5. Why DFS behaves like a stack.
6. How BFS explores levels.
7. How DFS backtracks.
8. How neighbor ordering affects traversal order.
9. How complexity depends on graph representation.
10. Where BFS and DFS are useful.

Once these ideas are clear, the C implementation becomes much easier to write yourself.


# 38. Iterative BFS and DFS

The repository also contains explicit iterative versions:

- [BFS/bfs_iterative.c](../BFS/bfs_iterative.c)
- [DFS/dfs_iterative.c](../DFS/dfs_iterative.c)

## Important Observation: BFS Is Already Iterative

BFS normally uses a queue and a loop:

    while queue is not empty:
        current = dequeue()
        process current

There is no need for recursive calls. Therefore, the original BFS implementation is already an **iterative BFS**.

The separate bfs_iterative.c file makes this explicit and gives the repository a consistent naming scheme.

## 39. Iterative DFS

The recursive DFS implementation hides the stack inside the programming language's call stack.

Recursive DFS:

    DFS(current)
        ↓
    DFS(neighbor)
        ↓
    DFS(next neighbor)

The computer stores these active function calls on the call stack.

Iterative DFS creates that stack ourselves:

    Stack s;

and uses:

    push()
    pop()
    isEmpty()

So we replace recursion with an explicit data structure.

## 40. Iterative DFS Algorithm

The basic algorithm is:

    1. Create visited array.
    2. Create empty stack.
    3. Push the starting vertex.
    4. While stack is not empty:
       a. Pop a vertex.
       b. If already visited, skip it.
       c. Mark it visited.
       d. Process it.
       e. Push its unvisited neighbors.

This is the same depth-first idea, but the stack is now visible in our code.

## 41. Why Does Iterative DFS Push Neighbors in Reverse Order?

Suppose the current vertex has neighbors:

    1, 2

A stack is LIFO.

If we push:

    push(1)
    push(2)

then the next vertex popped is:

    2

So the traversal may become:

    0 → 2 → ...

If we want the smaller-numbered neighbor to be processed first, we push in reverse order:

    push(2)
    push(1)

Now the top of the stack is 1, so:

    pop() → 1

This is why the iterative DFS code loops from vertices - 1 back down to 0.

This does not change the fundamental DFS algorithm. It only controls the neighbor-processing order.

## 42. Recursive DFS vs Iterative DFS

| Feature | Recursive DFS | Iterative DFS |
|---|---|---|
| Stack | Hidden call stack | Explicit stack |
| Main operation | Function call | push/pop |
| Code style | Shorter | More explicit |
| Risk | Deep recursion can overflow call stack | Explicit stack has controlled capacity |
| Concept | DFS through recursion | DFS through stack |

The important equivalence is:

    Recursive DFS
          ≈
    Explicit Stack DFS

Both implement depth-first exploration.

## 43. Iterative DFS Dry Run

Consider:

            0
           / \
          1   2
         / \   \
        3   4   5

Start at 0.

Initial stack:

    [0]

Pop 0 and visit it.

Neighbors are 1 and 2. Because we push in reverse order, we push 2 first and then 1:

    [2, 1]

The top is 1.

Pop 1 and visit it:

    Traversal: 0 1

Its unvisited neighbors are 3 and 4. Push 4 first, then 3:

    [2, 4, 3]

Pop 3:

    Traversal: 0 1 3

3 has no new neighbors.

Pop 4:

    Traversal: 0 1 3 4

Return to the stack. Pop 2:

    Traversal: 0 1 3 4 2

Then 2 discovers 5:

    Traversal: 0 1 3 4 2 5

So the iterative version can produce the same order as the recursive version when neighbor ordering is deliberately matched.

## 44. One Important Difference in visited Handling

There are two common iterative DFS styles.

### Style A — Mark when pushing

A vertex is marked visited when it enters the stack.

This prevents duplicate insertion.

### Style B — Mark when popping

A vertex is marked visited when it is removed from the stack.

Our implementation uses Style B and therefore checks:

    if (visited[current])
        continue;

This is useful for understanding the stack directly, but it can mean that the same vertex is temporarily pushed more than once in graphs with multiple paths to that vertex.

An alternative implementation can mark vertices when pushing them, similar to BFS.

## 45. Big Picture

Now the repository contains four useful implementations:

    BFS
     ├── bfs.c
     └── bfs_iterative.c

    DFS
     ├── dfs.c
     └── dfs_iterative.c

Conceptually:

    BFS
     ↓
    Queue + Loop

    DFS Recursive
     ↓
    Recursion + Hidden Stack

    DFS Iterative
     ↓
    Explicit Stack + Loop

This comparison is important because it shows that the traversal strategy and the implementation mechanism are related but not identical concepts.
