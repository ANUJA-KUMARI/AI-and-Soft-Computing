#include <stdio.h>

/*
 * Objective function:
 * f(x) = -(x - 5)^2 + 25
 *
 * We want to maximize this function.
 * Its global maximum is at x = 5, where f(x) = 25.
 */
int objectiveFunction(int x) {
    return -(x - 5) * (x - 5) + 25;
}

/*
 * Steepest-Ascent Hill Climbing:
 * 1. Generate every neighbor of the current state.
 * 2. Evaluate all neighbors.
 * 3. Select the neighbor with the highest value.
 * 4. Move only if that neighbor is better than the current state.
 */
void steepestAscentHillClimbing(int start) {
    int current = start;

    while (1) {
        int currentValue = objectiveFunction(current);

        /* In this example, the two neighbors are x - 1 and x + 1. */
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

        /*
         * If the best neighbor is not better than the current state,
         * we have reached a local optimum with respect to these moves.
         */
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
    int start;

    printf("Enter starting value of x: ");

    if (scanf("%d", &start) != 1) {
        printf("Invalid input. Please enter an integer.\n");
        return 1;
    }

    steepestAscentHillClimbing(start);

    return 0;
}
