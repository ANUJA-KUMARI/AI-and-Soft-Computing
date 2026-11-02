# Mamdani Fuzzy Inference System (FIS) — Python Lab

## 1. Aim

To implement a **Mamdani Fuzzy Inference System** in Python using a practical fan-speed control example.

The system takes two crisp inputs:
- Temperature (0 to 40 degrees)
- Humidity (0 to 100 percent)

It produces one crisp output:
- Fan speed (0% to 100%)

The program implements the complete Mamdani process without using an external fuzzy-logic library.

## 2. What is a Fuzzy Inference System?

A Fuzzy Inference System (FIS) uses fuzzy logic to map inputs to outputs using:
- Fuzzy sets
- Membership functions
- IF–THEN rules
- Fuzzy inference operators
- Defuzzification

Unlike a system that makes decisions only using strict true/false conditions, fuzzy logic allows partial truth values between 0 and 1.

For example, a temperature may be:
- Cold with membership 0.2
- Warm with membership 0.7
- Hot with membership 0.1

These degrees are used to evaluate fuzzy rules.

## 3. What is the Mamdani FIS?

The Mamdani model is a fuzzy inference method in which the rule consequent is a **fuzzy set**.

Example rule:

~~~text
IF temperature is HOT
AND humidity is HIGH
THEN fan speed is FAST
~~~

The rule's output is a fuzzy set such as FAST. After all rules are evaluated and combined, defuzzification converts the result into a crisp number.

## 4. Four Main Steps of Mamdani FIS

~~~text
Crisp Inputs
     |
     v
1. FUZZIFICATION
     |
     v
2. RULE EVALUATION
     |
     v
3. AGGREGATION
     |
     v
4. DEFUZZIFICATION
     |
     v
Crisp Output
~~~

### Step 1: Fuzzification

Convert crisp input values into membership degrees in their fuzzy sets.

For example, temperature = 35 may belong to:
- Warm to some degree
- Hot to some degree

### Step 2: Rule Evaluation

Evaluate every IF–THEN rule using the input membership degrees.

For an AND condition, this implementation uses the MIN operator:

~~~text
μ(A AND B) = min(μ(A), μ(B))
~~~

The result is called the **firing strength** or activation strength of the rule.

### Step 3: Aggregation

Combine the output fuzzy sets from all activated rules.

This implementation uses the MAX operator:

~~~text
μ_aggregated(y) = max(μ_rule1(y), μ_rule2(y), ...)
~~~

### Step 4: Defuzzification

Convert the aggregated fuzzy output into one crisp output.

This implementation uses the Centroid method:

~~~text
                 Σ [y × μ_aggregated(y)]
Crisp output =   ------------------------
                    Σ μ_aggregated(y)
~~~

The output universe is sampled at integer values from 0 to 100, so this is a discrete approximation of the centroid.

## 5. Example: Fan-Speed Controller

We want to control fan speed using temperature and humidity.

### Input 1: Temperature

Range: 0 to 40 degrees.

| Fuzzy set | Triangular parameters (a, b, c) |
|---|---|
| Cold | (0, 0, 20) |
| Warm | (10, 25, 40) |
| Hot | (30, 40, 40) |

The first and last sets are shoulder-shaped triangles:
- Cold is a left shoulder.
- Hot is a right shoulder.

### Input 2: Humidity

Range: 0 to 100%.

| Fuzzy set | Triangular parameters (a, b, c) |
|---|---|
| Dry | (0, 0, 50) |
| Normal | (25, 50, 75) |
| Humid | (50, 100, 100) |

### Output: Fan Speed

Range: 0 to 100%.

| Fuzzy set | Triangular parameters (a, b, c) |
|---|---|
| Slow | (0, 0, 50) |
| Medium | (25, 50, 75) |
| Fast | (50, 100, 100) |

The output sets are also triangular membership functions, including left and right shoulders.

## 6. Rule Base

The program uses these nine rules:

| Rule | IF temperature is | AND humidity is | THEN fan speed is |
|---:|---|---|---|
| 1 | Cold | Dry | Slow |
| 2 | Cold | Normal | Slow |
| 3 | Cold | Humid | Slow |
| 4 | Warm | Dry | Medium |
| 5 | Warm | Normal | Medium |
| 6 | Warm | Humid | Fast |
| 7 | Hot | Dry | Fast |
| 8 | Hot | Normal | Fast |
| 9 | Hot | Humid | Fast |

The rules are an illustrative control policy chosen for this lab.

## 7. Worked Numerical Example

Take:

~~~text
Temperature = 35
Humidity = 80
~~~

### Step 1: Fuzzification

For temperature = 35:

Warm = (40 - 35) / (40 - 25)

~~~text
μ(warm) = 5 / 15 = 0.333
~~~

Hot is a right shoulder with parameters (30, 40, 40):

~~~text
μ(hot) = (35 - 30) / (40 - 30) = 0.5
~~~

Cold membership is zero.

Therefore:

| Temperature set | Membership |
|---|---:|
| Cold | 0.000 |
| Warm | 0.333 |
| Hot | 0.500 |

For humidity = 80:

Humid is a right shoulder with parameters (50, 100, 100):

~~~text
μ(humid) = (80 - 50) / (100 - 50)
         = 30 / 50
         = 0.6
~~~

Dry and Normal membership are zero.

| Humidity set | Membership |
|---|---:|
| Dry | 0.000 |
| Normal | 0.000 |
| Humid | 0.600 |

### Step 2: Rule Evaluation

Only two rules have non-zero firing strength.

**Rule 6:**

~~~text
IF temperature is WARM AND humidity is HUMID
THEN fan speed is FAST
~~~

Using MIN:

~~~text
α₆ = min(0.333, 0.6)
   = 0.333
~~~

**Rule 9:**

~~~text
IF temperature is HOT AND humidity is HUMID
THEN fan speed is FAST
~~~

~~~text
α₉ = min(0.5, 0.6)
   = 0.5
~~~

Both rules activate the FAST output set. The strongest activation is 0.5 after MAX aggregation.

### Step 3: Aggregation

Each activated output membership function is clipped at its rule firing strength using MIN.

The clipped output sets are combined using MAX:

~~~text
μ_aggregated(y) = max(μ_rule1(y), ..., μ_rule9(y))
~~~

In this example, both active rules have the same consequent, FAST. The stronger activation determines the final clipped FAST set.

### Step 4: Defuzzification

Apply the discrete Centroid formula to the aggregated fan-speed membership values:

~~~text
                 Σ [y × μ_aggregated(y)]
Fan speed =      ------------------------
                    Σ μ_aggregated(y)
~~~

For this example, the program gives approximately:

~~~text
Fan speed = 80.82%
~~~

This is the crisp output of the example controller.

## 8. Understanding the Python Implementation

The code is stored at:

~~~text
Fuzzy-Inference-System/mamdani_fis.py
~~~

### A. Membership function

The function `triangular_membership()` calculates membership in a triangular fuzzy set. It also handles left and right shoulder sets where a = b or b = c.

### B. Fuzzification

The function `fuzzify()` calculates the membership degree of an input in every fuzzy set.

### C. Rule evaluation

~~~python
firing_strength = min(
    temperature_memberships[temperature_label],
    humidity_memberships[humidity_label],
)
~~~

This implements the Mamdani AND operator using MIN.

### D. Implication

~~~python
clipped_membership = min(firing_strength, output_membership)
~~~

This clips the consequent fuzzy set at the rule's firing strength.

### E. Aggregation

~~~python
aggregated_output[index] = max(
    aggregated_output[index], clipped_membership
)
~~~

This combines all rule outputs using MAX.

### F. Centroid

~~~python
weighted_sum = sum(
    value * membership
    for value, membership in zip(output_universe, aggregated_output)
)
crisp_fan_speed = weighted_sum / total_membership
~~~

This calculates the crisp fan-speed output from the aggregated fuzzy set.

## 9. Sample Input and Output

Input:

~~~text
Enter temperature: 35
Enter humidity (%): 80
~~~

Expected key output:

~~~text
Temperature memberships:
    cold: 0.000
    warm: 0.333
     hot: 0.500

Humidity memberships:
     dry: 0.000
  normal: 0.000
   humid: 0.600

Recommended fan speed = 80.82%
~~~

The program also prints the activated rules and their firing strengths.

## 10. How to Run

From the repository root:

~~~bash
python Fuzzy-Inference-System/mamdani_fis.py
~~~

Or:

~~~bash
python3 Fuzzy-Inference-System/mamdani_fis.py
~~~

## 11. Important Mamdani Operators

| Stage | Operator used in this program | Purpose |
|---|---|---|
| AND rule condition | MIN | Finds rule firing strength |
| Implication | MIN | Clips the consequent fuzzy set |
| Aggregation | MAX | Combines all rule outputs |
| Defuzzification | Centroid | Produces crisp output |

**Important:** Mamdani systems can use other fuzzy operators and defuzzification methods. This lab specifically uses MIN for AND and implication, MAX for aggregation, and Centroid for defuzzification.

## 12. Advantages

1. Intuitive and easy to understand.
2. Uses human-readable IF–THEN rules.
3. Handles imprecise inputs.
4. Produces interpretable fuzzy output sets.
5. Useful in control systems and decision-making.

## 13. Limitations

1. The rule base must be designed carefully.
2. Many input variables can create a large number of rules.
3. Membership-function choices affect the output.
4. Centroid calculation requires evaluating the aggregated output universe.

## 14. Important Exam / Viva Questions

**Q1. What is Mamdani FIS?**

A fuzzy inference system in which the consequent of each IF–THEN rule is a fuzzy set.

**Q2. What are the four steps of Mamdani FIS?**

Fuzzification, rule evaluation, aggregation, and defuzzification.

**Q3. Which operator is used for AND in this implementation?**

MIN.

**Q4. Which operator is used for aggregation?**

MAX.

**Q5. What is implication in Mamdani FIS?**

It applies the rule's firing strength to the consequent fuzzy set. Here, MIN clipping is used.

**Q6. Why is defuzzification required?**

To convert the final aggregated fuzzy output into a crisp numerical value.

**Q7. Which defuzzification method is used here?**

Centroid (Centre of Area).

**One-line answer:** Mamdani FIS converts crisp inputs into fuzzy memberships, evaluates IF–THEN rules, aggregates the fuzzy outputs, and defuzzifies them into a crisp result.

## 15. Quick Practice

Try:

~~~text
Temperature = 15
Humidity = 40
~~~

Observe:
1. The membership values for Cold, Warm, Dry, and Normal.
2. Which rules receive non-zero firing strengths?
3. How MIN determines each rule's strength.
4. How MAX combines the clipped output sets.
5. The final centroid fan speed.
