"""
Triangular Fuzzy Membership Function

Parameters:
    a: left endpoint (membership = 0)
    b: peak (membership = 1)
    c: right endpoint (membership = 0)

The parameters must satisfy a < b < c.
"""


def triangular_membership(x, a, b, c):
    """Return the membership degree of x in a triangular fuzzy set."""

    if not (a < b < c):
        raise ValueError("Parameters must satisfy a < b < c.")

    if x <= a or x >= c:
        return 0.0

    if x == b:
        return 1.0

    if x < b:
        # Increasing side of the triangle
        return (x - a) / (b - a)

    # Decreasing side of the triangle
    return (c - x) / (c - b)


def main():
    print("TRIANGULAR FUZZY MEMBERSHIP FUNCTION")

    try:
        a = float(input("Enter a (left endpoint): "))
        b = float(input("Enter b (peak): "))
        c = float(input("Enter c (right endpoint): "))

        if not (a < b < c):
            print("Invalid parameters: values must satisfy a < b < c.")
            return

        x = float(input("Enter input value x: "))

        degree = triangular_membership(x, a, b, c)

        print(f"\nMembership degree = {degree:.2f}")

    except ValueError as error:
        print(f"Invalid input: {error}")


if __name__ == "__main__":
    main()
