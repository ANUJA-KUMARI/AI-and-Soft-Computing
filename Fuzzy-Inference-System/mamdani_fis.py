"""
Mamdani Fuzzy Inference System (FIS)
Example: Fan-speed control using temperature and humidity.

Inference operators:
- AND: MIN
- Implication: MIN (clip the output membership function)
- Aggregation: MAX
- Defuzzification: Centroid

No external fuzzy-logic library is used.
"""


def triangular_membership(x, a, b, c):
    """Triangular membership function, including left/right shoulders."""
    if not (a <= b <= c):
        raise ValueError("Membership parameters must satisfy a <= b <= c.")

    # Left shoulder: membership remains 1 to the left of the peak.
    if a == b and x <= b:
        return 1.0

    # Right shoulder: membership remains 1 to the right of the peak.
    if b == c and x >= b:
        return 1.0

    if x <= a or x >= c:
        return 0.0

    if x == b:
        return 1.0

    if x < b:
        return (x - a) / (b - a)

    return (c - x) / (c - b)


# Fuzzy sets for the two input variables.
TEMPERATURE_SETS = {
    "cold": (0, 0, 20),
    "warm": (10, 25, 40),
    "hot": (30, 40, 40),
}

HUMIDITY_SETS = {
    "dry": (0, 0, 50),
    "normal": (25, 50, 75),
    "humid": (50, 100, 100),
}

# Fuzzy sets for the output variable (fan speed in percent).
FAN_SPEED_SETS = {
    "slow": (0, 0, 50),
    "medium": (25, 50, 75),
    "fast": (50, 100, 100),
}

# Rule format: (temperature label, humidity label, fan-speed label).
RULES = [
    ("cold", "dry", "slow"),
    ("cold", "normal", "slow"),
    ("cold", "humid", "slow"),

    ("warm", "dry", "medium"),
    ("warm", "normal", "medium"),
    ("warm", "humid", "fast"),

    ("hot", "dry", "fast"),
    ("hot", "normal", "fast"),
    ("hot", "humid", "fast"),
]


def fuzzify(value, fuzzy_sets):
    """Calculate membership of one crisp input in each fuzzy set."""
    return {
        label: triangular_membership(value, *parameters)
        for label, parameters in fuzzy_sets.items()
    }


def mamdani_inference(temperature, humidity):
    """Run fuzzification, rule evaluation, aggregation and centroid."""
    temperature_memberships = fuzzify(temperature, TEMPERATURE_SETS)
    humidity_memberships = fuzzify(humidity, HUMIDITY_SETS)

    # Discrete output universe: fan speed from 0% to 100%.
    output_universe = list(range(101))
    aggregated_output = [0.0] * len(output_universe)
    rule_results = []

    for temperature_label, humidity_label, output_label in RULES:
        # Mamdani AND operator: MIN of the two input memberships.
        firing_strength = min(
            temperature_memberships[temperature_label],
            humidity_memberships[humidity_label],
        )

        rule_results.append(
            (temperature_label, humidity_label, output_label, firing_strength)
        )

        # Mamdani implication: clip the rule's output fuzzy set using MIN.
        output_parameters = FAN_SPEED_SETS[output_label]

        for index, output_value in enumerate(output_universe):
            output_membership = triangular_membership(
                output_value, *output_parameters
            )
            clipped_membership = min(firing_strength, output_membership)

            # Aggregation: MAX across all rule output sets.
            aggregated_output[index] = max(
                aggregated_output[index], clipped_membership
            )

    total_membership = sum(aggregated_output)

    if total_membership == 0:
        raise ValueError(
            "No rule was activated. Check the input ranges and rule base."
        )

    # Centroid defuzzification for the discrete output universe.
    weighted_sum = sum(
        value * membership
        for value, membership in zip(output_universe, aggregated_output)
    )
    crisp_fan_speed = weighted_sum / total_membership

    return (
        temperature_memberships,
        humidity_memberships,
        rule_results,
        crisp_fan_speed,
    )


def main():
    print("MAMDANI FUZZY INFERENCE SYSTEM")
    print("Example: Fan-speed control")
    print("Temperature range: 0 to 40 degrees")
    print("Humidity range: 0 to 100 percent")

    try:
        temperature = float(input("\nEnter temperature: "))
        humidity = float(input("Enter humidity (%): "))

        if not 0 <= temperature <= 40:
            print("Temperature must be between 0 and 40.")
            return

        if not 0 <= humidity <= 100:
            print("Humidity must be between 0 and 100.")
            return

        temp_memberships, humidity_memberships, rule_results, fan_speed = (
            mamdani_inference(temperature, humidity)
        )

        print("\n1. FUZZIFICATION")
        print("Temperature memberships:")
        for label, degree in temp_memberships.items():
            print(f"  {label:>6}: {degree:.3f}")

        print("Humidity memberships:")
        for label, degree in humidity_memberships.items():
            print(f"  {label:>6}: {degree:.3f}")

        print("\n2. RULE EVALUATION (MIN)")
        for temp_label, humidity_label, output_label, strength in rule_results:
            if strength > 0:
                print(
                    f"  IF temperature is {temp_label} AND humidity is "
                    f"{humidity_label} THEN fan is {output_label}"
                    f"  | firing strength = {strength:.3f}"
                )

        print("\n3. AGGREGATION")
        print("  Rule output sets combined using MAX.")

        print("\n4. DEFUZZIFICATION (CENTROID)")
        print(f"  Recommended fan speed = {fan_speed:.2f}%")

    except ValueError as error:
        print(f"Invalid input: {error}")


if __name__ == "__main__":
    main()
