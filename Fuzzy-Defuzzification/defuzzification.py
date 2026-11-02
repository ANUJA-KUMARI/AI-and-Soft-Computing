"""
Defuzzification using:
1. Centroid (Centre of Area) method
2. Mean of Maxima (MOM) method

This program uses a discrete universe of discourse:
each x value has a corresponding membership degree.
"""


def centroid_method(universe, memberships):
    """Calculate the weighted average using membership degrees."""
    total_membership = sum(memberships)

    if total_membership == 0:
        raise ValueError("Centroid is undefined when all memberships are zero.")

    weighted_sum = 0.0

    for x, membership in zip(universe, memberships):
        weighted_sum += x * membership

    return weighted_sum / total_membership


def mean_of_maxima(universe, memberships):
    """Return the average of all x values with maximum membership."""
    maximum_membership = max(memberships)

    if maximum_membership == 0:
        raise ValueError("Mean of Maxima is undefined when all memberships are zero.")

    maximum_values = []

    for x, membership in zip(universe, memberships):
        if membership == maximum_membership:
            maximum_values.append(x)

    return sum(maximum_values) / len(maximum_values)


def main():
    print("DEFUZZIFICATION")
    print("Methods: Centroid and Mean of Maxima (MOM)")

    try:
        n = int(input("\nEnter the number of data points: "))

        if n <= 0:
            print("The number of data points must be positive.")
            return

        universe = []
        memberships = []

        print("\nEnter each universe value and its membership degree.")

        for i in range(n):
            print(f"\nData point {i + 1}:")
            x = float(input("  Universe value (x): "))
            membership = float(input("  Membership degree (0 to 1): "))

            if not 0.0 <= membership <= 1.0:
                print("Membership degree must be between 0 and 1.")
                return

            universe.append(x)
            memberships.append(membership)

        if any(universe[i] >= universe[i + 1] for i in range(n - 1)):
            print("Universe values must be entered in strictly increasing order.")
            return

        if max(memberships) == 0:
            print("At least one membership degree must be greater than zero.")
            return

        centroid = centroid_method(universe, memberships)
        mom = mean_of_maxima(universe, memberships)

        print("\nResults")
        print(f"Centroid method       = {centroid:.4f}")
        print(f"Mean of Maxima (MOM)  = {mom:.4f}")

    except ValueError as error:
        print(f"Invalid input: {error}")


if __name__ == "__main__":
    main()
