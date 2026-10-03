#include <stdio.h>
#include <limits.h>

#define MAX_NODES 20
#define MAX_CHILDREN 5

typedef struct {
    int children[MAX_CHILDREN];
    int costs[MAX_CHILDREN];
    int childCount;
    int isAnd;
    int solved;
    int heuristic;
    int bestChild;
} Node;

Node graph[MAX_NODES];

/*
 * This educational implementation assumes:
 * - An OR node chooses one child.
 * - An AND node requires all of its children.
 * - Costs are non-negative.
 * - The graph is acyclic.
 */
int aoStar(int node) {
    if (graph[node].solved) {
        return 0;
    }

    if (graph[node].childCount == 0) {
        graph[node].solved = 1;
        return 0;
    }

    if (!graph[node].isAnd) {
        int bestCost = INT_MAX;
        int bestChild = -1;

        for (int i = 0; i < graph[node].childCount; i++) {
            int child = graph[node].children[i];
            int childCost = graph[node].costs[i] + graph[child].heuristic;

            if (childCost < bestCost) {
                bestCost = childCost;
                bestChild = child;
            }
        }

        graph[node].bestChild = bestChild;
        aoStar(bestChild);

        graph[node].heuristic = graph[node].costs[0];

        for (int i = 0; i < graph[node].childCount; i++) {
            int child = graph[node].children[i];

            if (child == bestChild) {
                graph[node].heuristic = graph[node].costs[i] + graph[child].heuristic;
                break;
            }
        }

        if (graph[bestChild].solved) {
            graph[node].solved = 1;
        }
    } else {
        int totalCost = 0;
        int allSolved = 1;

        for (int i = 0; i < graph[node].childCount; i++) {
            int child = graph[node].children[i];

            aoStar(child);

            totalCost += graph[node].costs[i] + graph[child].heuristic;

            if (!graph[child].solved) {
                allSolved = 0;
            }
        }

        graph[node].heuristic = totalCost;

        if (allSolved) {
            graph[node].solved = 1;
        }
    }

    return graph[node].heuristic;
}

void printSolution(int node) {
    if (!graph[node].solved) {
        return;
    }

    printf("%d ", node);

    if (graph[node].isAnd) {
        for (int i = 0; i < graph[node].childCount; i++) {
            printSolution(graph[node].children[i]);
        }
    } else if (graph[node].bestChild != -1) {
        printSolution(graph[node].bestChild);
    }
}

int main(void) {
    /*
     * Example:
     *
     *          0 (OR)
     *         /      \
     *      1 (AND)    2
     *      /   \
     *     3     4
     *
     * Node 0 can choose node 1 or node 2.
     * If node 1 is chosen, both 3 and 4 are required.
     */

    for (int i = 0; i < MAX_NODES; i++) {
        graph[i].childCount = 0;
        graph[i].isAnd = 0;
        graph[i].solved = 0;
        graph[i].heuristic = 0;
        graph[i].bestChild = -1;
    }

    /* Node 0: OR node -> choose between 1 and 2. */
    graph[0].children[0] = 1;
    graph[0].costs[0] = 1;
    graph[0].children[1] = 2;
    graph[0].costs[1] = 4;
    graph[0].childCount = 2;

    /* Node 1: AND node -> both 3 and 4 are required. */
    graph[1].isAnd = 1;
    graph[1].children[0] = 3;
    graph[1].costs[0] = 2;
    graph[1].children[1] = 4;
    graph[1].costs[1] = 2;
    graph[1].childCount = 2;

    /* Node 2 is a terminal state. */
    graph[2].heuristic = 6;
    graph[2].solved = 1;

    /* Nodes 3 and 4 are terminal states. */
    graph[3].heuristic = 3;
    graph[3].solved = 1;

    graph[4].heuristic = 2;
    graph[4].solved = 1;

    aoStar(0);

    printf("AO* estimated solution cost: %d\n", graph[0].heuristic);
    printf("Solution graph: ");
    printSolution(0);
    printf("\n");

    return 0;
}
