# Triangular Fuzzy Membership Function — Python Lab

## 1. Aim

To implement a **Triangular Fuzzy Membership Function** in Python and calculate the degree to which an input value belongs to a fuzzy set.

## 2. What is a Fuzzy Membership Function?

In classical set theory, an element either belongs to a set or does not belong to it.

Fuzzy logic allows partial membership. A membership function maps an input value to a degree between 0 and 1:

~~~text
μ(x) ∈ [0, 1]
~~~

- **0:** no membership.
- **1:** full membership.
- **Between 0 and 1:** partial membership.

For example, a temperature may belong to the fuzzy set "Warm" with membership degree 0.6.

## 3. What is a Triangular Membership Function?

A triangular membership function is one of the simplest fuzzy membership functions. Its graph has a triangular shape and is defined by three parameters:

- **a:** left endpoint, where membership is 0.
- **b:** peak, where membership is 1.
- **c:** right endpoint, where membership is 0.

The parameters must satisfy:

~~~text
a < b < c
~~~

## 4. Mathematical Formula

~~~text
μ(x) = 0                 if x <= a or x >= c

       (x - a) / (b-a)   if a < x <= b

       (c - x) / (c-b)   if b < x < c
~~~

At x = b, both sides meet at membership 1. The formula can also be written as a separate case for x = b.

### Understand the three regions

1. **Outside the triangle:** membership is 0.
2. **Rising side (a to b):** membership increases linearly from 0 to 1.
3. **Falling side (b to c):** membership decreases linearly from 1 to 0.

## 5. Worked Example

Suppose:

~~~text
a = 10
b = 20
c = 30
~~~

| Input x | Calculation | Membership μ(x) |
|---:|---|---:|
| 5 | Outside triangle | 0.0 |
| 10 | Left endpoint | 0.0 |
| 12 | (12 - 10) / 10 | 0.2 |
| 15 | (15 - 10) / 10 | 0.5 |
| 18 | (18 - 10) / 10 | 0.8 |
| 20 | Peak | 1.0 |
| 22 | (30 - 22) / 10 | 0.8 |
| 25 | (30 - 25) / 10 | 0.5 |
| 28 | (30 - 28) / 10 | 0.2 |
| 30 | Right endpoint | 0.0 |
| 35 | Outside triangle | 0.0 |

For example, when x = 15:

~~~text
μ(15) = (15 - 10) / (20 - 10)
      = 5 / 10
      = 0.5
~~~

## 6. Shape of the Function

For a = 10, b = 20, and c = 30:

~~~text
Membership
1.0              /\
                /  \
0.5           /      \
             /        \
0.0 ________/__________\________
          10     20     30       x
                 Peak
~~~

The left side rises linearly and the right side falls linearly.

## 7. Algorithm

~~~text
TRIANGULAR-MEMBERSHIP(x, a, b, c)

1. Check that a < b < c.
   If not, report invalid parameters.

2. If x <= a or x >= c:
       return 0

3. If x == b:
       return 1

4. If x < b:
       return (x - a) / (b - a)

5. Otherwise:
       return (c - x) / (c - b)
~~~

## 8. Python Implementation

The program is stored at:

~~~text
Fuzzy-Membership-Functions/triangular_membership.py
~~~

It uses two parts:

- `triangular_membership(x, a, b, c)`: reusable function that calculates the membership degree.
- `main()`: reads values from the user, validates the parameters, calls the function, and displays the result.

No external fuzzy-logic library is used. The piecewise formula is implemented directly in Python.

## 9. Understanding the Python Code

### Parameter validation

~~~python
if not (a < b < c):
    raise ValueError("Parameters must satisfy a < b < c.")
~~~

The left endpoint must be smaller than the peak, and the peak must be smaller than the right endpoint. Otherwise, the triangle is invalid.

### Outside the triangle

~~~python
if x <= a or x >= c:
    return 0.0
~~~

At and outside the two endpoints, membership is zero.

### At the peak

~~~python
if x == b:
    return 1.0
~~~

The peak has full membership.

### Rising side

~~~python
if x < b:
    return (x - a) / (b - a)
~~~

This calculates the linearly increasing membership value.

### Falling side

~~~python
return (c - x) / (c - b)
~~~

If execution reaches this line, x is between b and c. This calculates the decreasing membership value.

## 10. Sample Input and Output

Input:

~~~text
Enter a (left endpoint): 10
Enter b (peak): 20
Enter c (right endpoint): 30
Enter input value x: 15
~~~

Output:

~~~text
Membership degree = 0.50
~~~

Therefore, x = 15 belongs to this fuzzy set with membership degree 0.5.

## 11. How to Run the Program

Open a terminal in the repository's root directory and run:

~~~bash
python Fuzzy-Membership-Functions/triangular_membership.py
~~~

If your system uses the `python3` command:

~~~bash
python3 Fuzzy-Membership-Functions/triangular_membership.py
~~~

## 12. Common Mistakes

1. **Invalid parameter order:** always check a < b < c.
2. **Forgetting endpoints:** membership is 0 at x = a and x = c.
3. **Forgetting the peak:** membership is 1 at x = b.
4. **Mixing up formulas:** use (x-a)/(b-a) on the rising side and (c-x)/(c-b) on the falling side.
5. **Using integer division in other languages:** membership values can be decimals, so use floating-point arithmetic. Python's `/` operator performs division and returns a floating-point result.

## 13. Important Exam Points

- A triangular membership function uses three parameters: a, b, and c.
- It has a piecewise linear shape.
- Membership values range from 0 to 1.
- At peak b, membership is 1.
- At and outside endpoints a and c, membership is 0.
- It is simple and computationally inexpensive.

**One-line answer:** A triangular membership function represents fuzzy-set membership using a triangle defined by a left endpoint a, peak b, and right endpoint c.

## 14. Quick Practice

Try:

~~~text
a = 0
b = 5
c = 10
~~~

Calculate μ(x) for x = 0, 2, 5, 7, 10, and 12.

Expected values:

~~~text
0.0, 0.4, 1.0, 0.6, 0.0, 0.0
~~~
