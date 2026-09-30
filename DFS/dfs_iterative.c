#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

typedef struct {
    int items[MAX_VERTICES];
    int top;
} Stack;

void initStack(Stack *s) {
    s->top = -1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

void push(Stack *s, int value) {
    if (s->top == MAX_VERTICES - 1) {
        printf("Stack overflow.\n");
        exit(EXIT_FAILURE);
    }

    s->items[++s->top] = value;
}

int pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack underflow.\n");
        exit(EXIT_FAILURE);
    }

    return s->items[s->top--];
}

void dfsIterative(int graph[MAX_VERTICES][MAX_VERTICES],
                  int vertices,
                  int start) {
    int visited[MAX_VERTICES] = {0};
    Stack s;

    initStack(&s);

    push(&s, start);

    printf("Iterative DFS Traversal: ");

    while (!isEmpty(&s)) {
        int current = pop(&s);

        if (visited[current]) {
            continue;
        }

        visited[current] = 1;
        printf("%d ", current);

        /*
         * Push neighbors in reverse order so that the
         * smallest-numbered neighbor is processed first.
         */
        for (int next = vertices - 1; next >= 0; next--) {
            if (graph[current][next] && !visited[next]) {
                push(&s, next);
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

    dfsIterative(graph, vertices, start);

    return 0;
}
