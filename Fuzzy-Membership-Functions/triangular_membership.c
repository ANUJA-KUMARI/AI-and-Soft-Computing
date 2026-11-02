#include <stdio.h>

/*
 * Triangular Fuzzy Membership Function
 * a = left endpoint (membership 0)
 * b = peak (membership 1)
 * c = right endpoint (membership 0)
 * Required condition: a < b < c
 */
double triangularMembership(double x, double a, double b, double c) {
    if (x <= a || x >= c) return 0.0;
    if (x == b) return 1.0;
    if (x < b) return (x - a) / (b - a);
    return (c - x) / (c - b);
}

int main(void) {
    double a, b, c, x;

    printf("TRIANGULAR FUZZY MEMBERSHIP FUNCTION\n");

    printf("Enter a (left endpoint): ");
    if (scanf("%lf", &a) != 1) {
        printf("Invalid numeric input.\n");
        return 1;
    }

    printf("Enter b (peak): ");
    if (scanf("%lf", &b) != 1) {
        printf("Invalid numeric input.\n");
        return 1;
    }

    printf("Enter c (right endpoint): ");
    if (scanf("%lf", &c) != 1) {
        printf("Invalid numeric input.\n");
        return 1;
    }

    if (!(a < b && b < c)) {
        printf("Invalid parameters: values must satisfy a < b < c.\n");
        return 1;
    }

    printf("Enter input value x: ");
    if (scanf("%lf", &x) != 1) {
        printf("Invalid numeric input.\n");
        return 1;
    }

    printf("\nMembership degree = %.2f\n",
           triangularMembership(x, a, b, c));

    return 0;
}
