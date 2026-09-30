#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

typedef struct {
    int items[MAX_VERTICES];
    int front;
    int rear;
} Queue;

void initQueue(Queue *q) {
    q->front = 0;
    q->rear = -1;
}

int isEmpty(Queue *q) {
    return q->rear < q->front;
}

void enqueue(Queue *q, int value) {
    if (q->rear == MAX_VERTICES - 1) {
        printf("Queue overflow.\n");
        exit(EXIT_FAILURE);
    }

    q->items[++q->rear] = value;
}

int dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue underflow.\n");
        exit(EXIT_FAILURE);
    }

    return q->items[q->front++];
}

void bfs(int graph[MAX_VERTICES][MAX_VERTICES], int vertices, int start) {
    int visited[MAX_VERTICES] = {0};
    Queue q;

    initQueue(&q);
    visited[start] = 1;
    enqueue(&q, start);

    printf("BFS Traversal: ");

    while (!isEmpty(&q)) {
        int current = dequeue(&q);
        printf("%d ", current);

        for (int next = 0; next < vertices; next++) {
            if (graph[current][next] && !visited[next]) {
                visited[next] = 1;
                enqueue(&q, next);
            }
        }
    }

    printf("\n");
}

int main(void) {
    int graph[MAX_VERTICES][MAX_VERTICES] = {0};
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

    bfs(graph, vertices, start);

    return 0;
}
