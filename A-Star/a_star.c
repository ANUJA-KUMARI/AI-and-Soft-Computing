#include <stdio.h>

#define MAX 20
#define INF 999999

int main(void) {
    int n, edges;
    int graph[MAX][MAX] = {0};
    int heuristic[MAX];
    int g[MAX], parent[MAX];
    int open[MAX] = {0}, closed[MAX] = {0};
    int start, goal;

    printf("Enter number of nodes (maximum %d): ", MAX);
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX) {
        printf("Invalid number of nodes.\n");
        return 1;
    }

    printf("Enter number of edges: ");
    if (scanf("%d", &edges) != 1 || edges < 0 || edges > n * (n - 1) / 2) {
        printf("Invalid number of edges.\n");
        return 1;
    }

    printf("Enter each edge as: node1 node2 cost\n");
    printf("Use node numbers from 0 to %d.\n", n - 1);

    for (int i = 0; i < edges; i++) {
        int u, v, cost;
        if (scanf("%d %d %d", &u, &v, &cost) != 3 ||
            u < 0 || u >= n || v < 0 || v >= n || cost <= 0) {
            printf("Invalid edge input.\n");
            return 1;
        }
        graph[u][v] = cost;
        graph[v][u] = cost;
    }

    printf("Enter heuristic value for each node:\n");
    for (int i = 0; i < n; i++) {
        printf("h(%d) = ", i);
        if (scanf("%d", &heuristic[i]) != 1 || heuristic[i] < 0) {
            printf("Invalid heuristic value.\n");
            return 1;
        }
    }

    printf("Enter start node and goal node: ");
    if (scanf("%d %d", &start, &goal) != 2 ||
        start < 0 || start >= n || goal < 0 || goal >= n) {
        printf("Invalid start or goal node.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        g[i] = INF;
        parent[i] = -1;
    }

    g[start] = 0;
    open[start] = 1;

    while (1) {
        int current = -1;
        int bestF = INF;

        for (int i = 0; i < n; i++) {
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
        closed[current] = 1;

        for (int next = 0; next < n; next++) {
            if (graph[current][next] > 0) {
                int newG = g[current] + graph[current][next];

                if (newG < g[next]) {
                    g[next] = newG;
                    parent[next] = current;
                    open[next] = 1;
                    closed[next] = 0;
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
