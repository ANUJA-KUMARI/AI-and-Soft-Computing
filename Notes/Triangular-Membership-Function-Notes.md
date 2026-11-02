# Triangular Fuzzy Membership Function — Complete Notes

## 1. What is a Fuzzy Membership Function?

In classical set theory, an element either belongs to a set or does not belong to it. Fuzzy logic allows partial membership.

A membership function maps an input value to a degree between 0 and 1:

~~~text
μ(x) ∈ [0, 1]
~~~

- 0 means no membership.
- 1 means full membership.
- A value between 0 and 1 means partial membership.

For example, a temperature might belong to the fuzzy set "Warm" with membership degree 0.6.

## 2. What is a Triangular Membership Function?

A triangular membership function is one of the simplest fuzzy membership functions. It has a triangle-shaped graph defined by three parameters:

- **a:** left endpoint; membership is 0.
- **b:** peak; membership is 1.
- **c:** right endpoint; membership is 0.

The parameters must satisfy:

~~~text
a < b < c
~~~

## 3. Mathematical Formula

~~~text
             0,                  x <= a or x >= c

             (x - a) / (b - a), a < x < b

μ(x) =       1,                  x = b

             (c - x) / (c - b), b < x < c
~~~

The result is always between 0 and 1 when the parameters are valid.

## 4. Understand the Regions

**Outside the triangle:** If x <= a or x >= c, membership is 0.

**Increasing slope:** If a < x < b:

~~~text
μ(x) = (x - a) / (b - a)
~~~

Membership increases linearly from 0 to 1.

**Peak:** At x = b:

~~~text
μ(x) = 1
~~~

**Decreasing slope:** If b < x < c:

~~~text
μ(x) = (c - x) / (c - b)
~~~

Membership decreases linearly from 1 to 0.

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

if a >= b or b >= c:
    report invalid parameters

if x <= a or x >= c:
    return 0

if x == b:
    return 1

if x < b:
    return (x - a) / (b - a)

otherwise:
    return (c - x) / (c - b)
~~~

## 8. C Implementation

The program is stored at:

~~~text
Fuzzy-Membership-Functions/triangular_membership.c
~~~

It reads a, b, c, and x; validates the parameter order; calculates the membership degree; and prints the result.

The function uses the double data type because membership values can be decimal numbers such as 0.25, 0.6, or 0.85.

## 9. Understanding the Code

**Endpoint check**

~~~c
if (x <= a || x >= c) return 0.0;
~~~

At and outside the endpoints, membership is zero.

**Peak check**

~~~c
if (x == b) return 1.0;
~~~

At the peak, membership is one.

**Increasing side**

~~~c
if (x < b) return (x - a) / (b - a);
~~~

This calculates the rising side.

**Decreasing side**

~~~c
return (c - x) / (c - b);
~~~

After the earlier checks, this calculates the falling side.

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

Calculation:

~~~text
μ(15) = (15 - 10) / (20 - 10)
      = 5 / 10
      = 0.5
~~~

So, input 15 belongs to this fuzzy set with membership degree 0.5.

## 11. Compile and Run

From the repository root:

~~~bash
gcc Fuzzy-Membership-Functions/triangular_membership.c -o triangular_membership
./triangular_membership
~~~

## 12. Common Mistakes

1. **Using integer division:** use double values so results such as 0.5 are not truncated.
2. **Invalid parameter order:** always check a < b < c.
3. **Forgetting endpoints:** membership is 0 at x = a and x = c.
4. **Forgetting the peak:** membership is 1 at x = b.
5. **Mixing up formulas:** use (x - a)/(b - a) on the rising side and (c - x)/(c - b) on the falling side.

## 13. Important Exam Points

- A triangular membership function uses three parameters: a, b, and c.
- It has a piecewise linear shape.
- Membership values range from 0 to 1.
- At peak b, membership is 1.
- At and outside endpoints a and c, membership is 0.
- It is simple and computationally inexpensive.

**One-line answer:** A triangular membership function represents fuzzy-set membership using a triangle defined by left endpoint a, peak b, and right endpoint c.

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
