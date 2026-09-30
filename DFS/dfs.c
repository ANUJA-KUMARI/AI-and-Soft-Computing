#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

void dfs(int graph[MAX_VERTICES][MAX_VERTICES],
         int vertices,
         int current,
         int visited[MAX_VERTICES]) {
    visited[current] = 1;
    printf("%d ", current);

    for (int next = 0; next < vertices; next++) {
        if (graph[current][next] && !visited[next]) {
            dfs(graph, vertices, next, visited);
        }
    }
}

int main(void) {
    int graph[MAX_VERTICES][MAX_VERTICES] = {0};
    int visited[MAX_VERTICES] = {0};
    int vertices, edges, start;

    printf("Enter number of vertices: ");
    scanf("%d", &vertices);

    if (vertices <= 0 || vertices > MAX_VERTICES) {
        printf("Invalid number of vertices.\n");
        return EXIT_FAILURE;
    }

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    if (edges < 0) {
        printf("Invalid number of edges.\n");
        return EXIT_FAILURE;
    }

    printf("Enter each edge as: source destination\n");
    for (int i = 0; i < edges; i++) {
        int u, v;
        scanf("%d %d", &u, &v);

        if (u < 0 || u >= vertices || v < 0 || v >= vertices) {
            printf("Invalid edge: %d %d\n", u, v);
            return EXIT_FAILURE;
        }

        graph[u][v] = 1;
        graph[v][u] = 1;
    }

    printf("Enter starting vertex: ");
    scanf("%d", &start);

    if (start < 0 || start >= vertices) {
        printf("Invalid starting vertex.\n");
        return EXIT_FAILURE;
    }

    printf("DFS Traversal: ");
    dfs(graph, vertices, start, visited);
    printf("\n");

    return 0;
}
