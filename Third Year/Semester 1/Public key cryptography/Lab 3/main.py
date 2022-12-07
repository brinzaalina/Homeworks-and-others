# Pollard p-1 algorithm
# based also on Fermat's Little Theorem, which states that a^p = a (mod p), when p is prime, for every integer number a
# a^k = 1 (mod p) for every integer k, when p does not divide a => p | a^k - 1
# if n does not divide a^k - 1, then d = gcd(a^k - 1, n) is a non-trivial factor of n
# we choose k as the lowest common multiple of the numbers 1, 2, ..., B, where B is the bound
# this means that if the primes dividing p - 1 are smaller than B, then k is a multiple of p - 1


import random


def compute_gcd(x, y):
    # This function implements the Euclidean algorithm to compute GCD
    if x == 0:
        return y
    return compute_gcd(y % x, x)


def compute_lcm(x, y):
    # This function takes two integers and returns the LCM
    g = compute_gcd(x, y)
    return (x * y) // g


def compute_lcm_list(numbers):
    # This function takes a list of integers and returns the LCM of all the numbers
    if len(numbers) == 0:
        return -1
    elif len(numbers) == 1:
        return numbers[0]
    else:
        lcm = compute_lcm(numbers[0], numbers[1])
        for i in range(2, len(numbers)):
            lcm = compute_lcm(lcm, numbers[i])
        return lcm


def binary_decomposition(k):
    # This function takes an integer and returns a list of the orders of powers of 2 that compose it
    # e.g. 13 = 1101
    # returns [0, 2, 3]
    v = []
    decomposition = []
    while k > 0:
        v.append(k % 2)
        k = k // 2
    for i in range(0, len(v)):
        if v[i] == 1:
            decomposition.append(i)
    return decomposition


def compute_modular_squaring(a, k, n):
    # This function takes an integer a, an integer k and an integer n and returns a^k (mod n)
    sum = binary_decomposition(k)
    rests = []

    stop = sum[-1]
    aux = a % n
    for i in range(0, stop + 1):
        if i in sum:
            rests.append(aux)
        aux = (aux * aux) % n
    result = 1
    for i in rests:
        result = (result * i) % n
    return result


def pollard_p_1(n, B=13, a=2):
    # This function takes an integer n and returns a non-trivial factor of n
    # B is the bound
    # a is the base
    k_list = []
    for i in range(1, B + 1):
        k_list.append(i)
    k = compute_lcm_list(k_list)
    if a != 2:
        a = random.randint(2, n - 2)
    a = compute_modular_squaring(a, k, n)
    d = compute_gcd(a - 1, n)
    return d


def get_nontrivial_factor(n):
    B = int(input("Enter the bound: "))
    if B == 0:
        f = pollard_p_1(n)
    else:
        f = pollard_p_1(n, B)
    if f == 1 or f == n:
        print("Failure")
        get_nontrivial_factor(n)
    else:
        print("Nontrivial factor found: " + str(f) + " => " + str(n) + " = " + str(f) + " * " + str(n // f))


def main():
    n = int(input("Enter an odd composite number: "))
    get_nontrivial_factor(n)


main()
