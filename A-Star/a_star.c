#include <stdio.h>

#define MAX 5
#define INF 999999

int main(void) {
    int graph[MAX][MAX] = {
        {0, 1, 4, 0, 0},
        {1, 0, 0, 2, 0},
        {4, 0, 0, 1, 0},
        {0, 2, 1, 0, 3},
        {0, 0, 0, 3, 0}
    };

    int heuristic[MAX] = {5, 4, 2, 2, 0};
    int g[MAX], parent[MAX];
    int open[MAX] = {0};

    int start = 0;
    int goal = 4;

    for (int i = 0; i < MAX; i++) {
        g[i] = INF;
        parent[i] = -1;
    }

    g[start] = 0;
    open[start] = 1;

    while (1) {
        int current = -1;
        int bestF = INF;

        for (int i = 0; i < MAX; i++) {
            if (open[i] && g[i] + heuristic[i] < bestF) {
                bestF = g[i] + heuristic[i];
                current = i;
            }
        }

        if (current == -1) {
            printf("No path found.\n");
            return 0;
        }

        if (current == goal) {
            break;
        }

        open[current] = 0;

        for (int next = 0; next < MAX; next++) {
            if (graph[current][next] > 0) {
                int newG = g[current] + graph[current][next];

                if (newG < g[next]) {
                    g[next] = newG;
                    parent[next] = current;
                    open[next] = 1;
                }
            }
        }
    }

    int path[MAX];
    int pathLength = 0;
    int node = goal;

    while (node != -1) {
        path[pathLength++] = node;
        node = parent[node];
    }

    printf("Start node: %d\n", start);
    printf("Goal node: %d\n", goal);

    printf("Shortest path: ");
    for (int i = pathLength - 1; i >= 0; i--) {
        printf("%d", path[i]);
        if (i > 0) {
            printf(" -> ");
        }
    }

    printf("\nTotal path cost: %d\n", g[goal]);

    return 0;
}