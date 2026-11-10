#include <stdio.h>

int objectiveFunction(int x) {
    return -(x - 5) * (x - 5) + 25;
}

void steepestAscentHillClimbing(int current) {

    while (1) {
        int currentValue = objectiveFunction(current);

        int neighbors[2] = {current - 1, current + 1};

        int bestNeighbor = current;
        int bestNeighborValue = currentValue;

        printf("\nCurrent state: x = %d, f(x) = %d\n",
               current, currentValue);

        printf("Evaluating all neighbors:\n");

        for (int i = 0; i < 2; i++) {
            int neighbor = neighbors[i];
            int neighborValue = objectiveFunction(neighbor);

            printf("  x = %d, f(x) = %d\n", neighbor, neighborValue);

            if (neighborValue > bestNeighborValue) {
                bestNeighbor = neighbor;
                bestNeighborValue = neighborValue;
            }
        }

        if (bestNeighbor == current) {
            printf("\nNo better neighbor exists. Search stopped.\n");
            break;
        }

        printf("Moving to the best neighbor: x = %d\n", bestNeighbor);
        current = bestNeighbor;
    }

    printf("\nSteepest-Ascent Hill Climbing result:\n");
    printf("Best state found: x = %d\n", current);
    printf("Objective value: f(x) = %d\n", objectiveFunction(current));
}

int main(void) {
    int current;

    printf("Enter starting value of x: ");

    if (scanf("%d", &current) != 1) {
        printf("Invalid input. Please enter an integer.\n");
        return 1;
    }

    steepestAscentHillClimbing(current);

    return 0;
}
