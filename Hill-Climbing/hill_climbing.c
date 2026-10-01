#include <stdio.h>

/*
 * Objective function:
 * f(x) = -(x - 5)^2 + 25
 *
 * The maximum value is reached at x = 5.
 */
int objectiveFunction(int x) {
    return -(x - 5) * (x - 5) + 25;
}

void hillClimbing(int start) {
    int current = start;

    while (1) {
        int currentValue = objectiveFunction(current);
        int left = current - 1;
        int right = current + 1;
        int leftValue = objectiveFunction(left);
        int rightValue = objectiveFunction(right);

        printf("Current state: x = %d, f(x) = %d\\n", current, currentValue);

        if (leftValue > currentValue && leftValue >= rightValue) {
            current = left;
        } else if (rightValue > currentValue) {
            current = right;
        } else {
            break;
        }
    }

    printf("\\nHill Climbing stopped at: x = %d\\n", current);
    printf("Maximum value found: f(x) = %d\\n", objectiveFunction(current));
}

int main(void) {
    int start;

    printf("Enter starting value of x: ");
    scanf("%d", &start);

    hillClimbing(start);

    return 0;
}
