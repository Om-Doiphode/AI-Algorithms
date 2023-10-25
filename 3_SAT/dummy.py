from string import ascii_lowercase
from itertools import combinations
import numpy as np
import random

print("Enter the number of clauses in the formula")
m = 4
print("Enter the number of literals in a clause ")
k = 3
print("Enter number of variables ")
n = 4

def makeProblem(m, k, n):
    pos_var = (list(ascii_lowercase))[:n]
    neg_var = [c.upper() for c in pos_var]
    variables = pos_var + neg_var
    t_hold = 10
    problems = []
    allCombos = list(combinations(variables, k))
    i = 0

    while i<t_hold:
        x = random.sample(allCombos, m)
        if x not in problems:
            i += 1
            problems.append(list(x))
    return variables, problems


def assignment(variables, n):
    forPositive = list(np.random.choice(2,n))
    print(forPositive)
    forNegative = [abs(1-i) for i in forPositive]
    print(forNegative)
    assign = forPositive + forNegative
    print(assign)
    var_assign = dict(zip(variables, assign))
    return var_assign

variables, problems = makeProblem(m, k, n)
# print(variables)
# print(problems)
print(assignment(variables,n))