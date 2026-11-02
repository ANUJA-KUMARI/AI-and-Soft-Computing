# Defuzzification — Centroid and Mean of Maxima (Python Lab)

## 1. Aim

To implement two defuzzification methods in Python:

1. Centroid (Centre of Area) method
2. Mean of Maxima (MOM) method

The program converts fuzzy output membership values into crisp numerical values.

## 2. What is Defuzzification?

A fuzzy inference system can produce fuzzy output rather than one exact number.

Defuzzification converts this fuzzy output into a single **crisp value** that can be used to make a decision.

Example: a fuzzy controller may produce an output representing a fan speed. Defuzzification converts the fuzzy result into one numerical fan-speed value.

~~~text
Fuzzy output
     |
     v
Defuzzification
     |
     v
Crisp numerical output
~~~

## 3. Discrete Universe of Discourse

Our Python program uses a discrete universe of discourse. This means we are given a list of output values and their corresponding membership degrees.

For example:

| Universe value (x) | Membership degree μ(x) |
|---:|---:|
| 0 | 0.0 |
| 1 | 0.1 |
| 2 | 0.2 |
| 3 | 0.4 |
| 4 | 0.6 |
| 5 | 0.8 |
| 6 | 0.8 |
| 7 | 0.6 |
| 8 | 0.4 |
| 9 | 0.2 |
| 10 | 0.0 |

Each x value is paired with the membership degree at that value.

**Important:** The formulas below are the discrete versions of the methods. The centroid for a continuous membership function is calculated using integrals.

# 4. Centroid Method (Centre of Area)

The Centroid method finds the balance point or centre of gravity of the fuzzy output.

Think of the membership graph as a flat shape. The centroid is the point at which that shape would balance.

### Formula

For discrete output values:

~~~text
                 Σ [xᵢ × μ(xᵢ)]
Centroid =       ----------------
                    Σ μ(xᵢ)
~~~

Where:
- xᵢ = each output value in the universe.
- μ(xᵢ) = membership degree corresponding to xᵢ.
- Σ = summation over all data points.

### Step-by-step example

Using our table:

~~~text
x          = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10]

μ(x)       = [0, .1, .2, .4, .6, .8, .8, .6, .4, .2, 0]
~~~

First calculate the sum of membership degrees:

~~~text
Σ μ(xᵢ) = 0 + 0.1 + 0.2 + 0.4 + 0.6
          + 0.8 + 0.8 + 0.6 + 0.4 + 0.2 + 0

        = 4.1
~~~

Now calculate the weighted sum:

~~~text
Σ [xᵢ × μ(xᵢ)]
= (0×0) + (1×0.1) + (2×0.2) + (3×0.4)
  + (4×0.6) + (5×0.8) + (6×0.8)
  + (7×0.6) + (8×0.4) + (9×0.2) + (10×0)

= 20.5
~~~

Therefore:

~~~text
Centroid = 20.5 / 4.1
         = 5.0
~~~

**Final centroid = 5.0**

# 5. Mean of Maxima (MOM) Method

The Mean of Maxima method finds all universe values that have the **maximum membership degree** and calculates their arithmetic mean.

In simple words:

1. Find the highest membership value.
2. Identify every x value having that membership.
3. Calculate the average of those x values.

### Formula

If the maximum membership occurs at m points:

~~~text
              x₁ + x₂ + ... + xₘ
MOM =         -------------------
                       m
~~~

Here, x₁, x₂, ..., xₘ are all universe values at which membership is maximum.

### Step-by-step example

From our table:

~~~text
μ(x) = [0, 0.1, 0.2, 0.4, 0.6, 0.8,
        0.8, 0.6, 0.4, 0.2, 0]
~~~

The maximum membership degree is:

~~~text
Maximum membership = 0.8
~~~

It occurs at:

~~~text
x = 5 and x = 6
~~~

Therefore:

~~~text
MOM = (5 + 6) / 2
    = 11 / 2
    = 5.5
~~~

**Final MOM = 5.5**

If the maximum membership occurs at only one point, MOM is simply that point.

# 6. Compare the Results

For the example dataset:

| Method | Crisp output |
|---|---:|
| Centroid | 5.0 |
| Mean of Maxima | 5.5 |

Why are the answers different?

- Centroid considers **all membership values** and calculates a weighted balance point.
- MOM considers **only the values having the maximum membership**.

# 7. Algorithm

~~~text
INPUT:
    n
    universe values x[0...n-1]
    membership values mu[0...n-1]

CENTROID:
    numerator = 0
    denominator = 0

    for each data point i:
        numerator += x[i] * mu[i]
        denominator += mu[i]

    centroid = numerator / denominator

MEAN OF MAXIMA:
    maximum = largest value in mu
    sum = 0
    count = 0

    for each data point i:
        if mu[i] == maximum:
            sum += x[i]
            count += 1

    MOM = sum / count

DISPLAY centroid and MOM
~~~

# 8. Python Implementation

The program is stored at:

~~~text
Fuzzy-Defuzzification/defuzzification.py
~~~

It contains two separate functions:

- `centroid_method(universe, memberships)`
- `mean_of_maxima(universe, memberships)`

The `main()` function reads the data points, validates the input, calls both methods, and displays their results.

No external fuzzy-logic library is used.

# 9. Understanding the Code

### Centroid calculation

~~~python
total_membership = sum(memberships)
weighted_sum = 0.0

for x, membership in zip(universe, memberships):
    weighted_sum += x * membership

return weighted_sum / total_membership
~~~

- `sum(memberships)` calculates the denominator.
- `zip(universe, memberships)` pairs each x value with its membership.
- `x * membership` calculates the weighted contribution.
- Dividing the weighted sum by total membership gives the centroid.

### Mean of Maxima calculation

~~~python
maximum_membership = max(memberships)
maximum_values = []

for x, membership in zip(universe, memberships):
    if membership == maximum_membership:
        maximum_values.append(x)

return sum(maximum_values) / len(maximum_values)
~~~

- `max(memberships)` finds the highest membership degree.
- The loop collects every x value that has this maximum degree.
- The average of those x values is the MOM result.

### Input validation

The program checks that:
- The number of data points is positive.
- Membership degrees lie between 0 and 1.
- Universe values are entered in strictly increasing order.
- At least one membership degree is greater than zero.

If every membership is zero, both methods are undefined for this program's fuzzy output, so it reports an error instead of dividing by zero or averaging every universe value.

# 10. Sample Input and Output

Input:

~~~text
Enter the number of data points: 11

Data point 1:
  Universe value (x): 0
  Membership degree (0 to 1): 0

Data point 2:
  Universe value (x): 1
  Membership degree (0 to 1): 0.1

... enter the remaining pairs from the example table ...
~~~

Expected output for the complete example dataset:

~~~text
Results
Centroid method       = 5.0000
Mean of Maxima (MOM)  = 5.5000
~~~

# 11. How to Run

From the repository root:

~~~bash
python Fuzzy-Defuzzification/defuzzification.py
~~~

If your system uses `python3`:

~~~bash
python3 Fuzzy-Defuzzification/defuzzification.py
~~~

# 12. Centroid vs Mean of Maxima

| Feature | Centroid | Mean of Maxima |
|---|---|---|
| Main idea | Centre of gravity / weighted average | Average of maximum-membership positions |
| Uses | All membership values | Only maximum-membership positions |
| Output | Weighted balance point | Mean of peak positions |
| Multiple maximum points | Naturally included through weighting | Explicitly averages all maximum points |
| Common limitation | Requires summation / integration | Ignores non-maximum membership values |

# 13. Important Exam Points

- Defuzzification converts fuzzy output into a crisp value.
- Centroid is also called Centre of Area or Centre of Gravity.
- Centroid uses a weighted average of all output values.
- Mean of Maxima finds the mean of all values having maximum membership.
- The two methods can produce different crisp outputs.
- For a discrete universe, use summation; for a continuous membership function, centroid is commonly expressed using integrals.

**One-line answers:**

- **Centroid:** Finds the weighted centre of the fuzzy output membership distribution.
- **MOM:** Finds the average of all output values that have the maximum membership degree.

# 14. Quick Practice

Use:

~~~text
x  = [1, 2, 3, 4, 5]
μ  = [0.2, 0.5, 1.0, 1.0, 0.4]
~~~

Questions:
1. What is the maximum membership degree?
2. At which x values does it occur?
3. Calculate MOM.
4. Calculate the centroid.

Expected MOM:

~~~text
MOM = (3 + 4) / 2 = 3.5
~~~
