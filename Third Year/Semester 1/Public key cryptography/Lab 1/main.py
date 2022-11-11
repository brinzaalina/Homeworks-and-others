import datetime


def gcd_euclidean(x, y):
    """
    Compute the GCD of 2 numbers using the Euclidean algorithm
    """
    if x == 0 or x == y:
        return y
    elif y == 0:
        return x
    while y > 0:
        temp = x % y
        x = y
        y = temp
    return x


def gcd_prime_factors(x, y):
    """
    Compute the GCD of 2 numbers by decomposing the numbers into products of prime factors
    The GCD is the product of the common factors, taken at the lowest power.
    """
    if x == 0 or x == y:
        return y
    elif y == 0:
        return x
    i = 2
    greatest_common_divisor = 1
    while x > i or y > i:
        while x % i == 0 and y % i == 0:
            greatest_common_divisor *= i
            x //= i
            y //= i
        i += 1
    return greatest_common_divisor


def gcd_brute_force(x, y):
    """
    Consider the GCD as being the smallest number between the given two and subtract from this number until it divides
    both numbers
    """
    if x == 0 or x == y:
        return y
    elif y == 0:
        return x
    greatest_common_divisor = min(x, y)
    while x % greatest_common_divisor != 0 or y % greatest_common_divisor != 0:
        greatest_common_divisor -= 1
    return greatest_common_divisor


if __name__ == '__main__':
    tests = [
        (18, 12),
        (30, 17),
        (45, 70),
        (255, 300),
        (255, 177),
        (101, 301),
        (4137524, 1227244),
        # (294733, 10383680172),
        (4 ** 4, 6 ** 4),
        # (2 ** 50, 4 ** 20),
        (6 ** 3, 3 ** 7),
        # (12345665434562, 57658787675842),
        (182364, 116033),
        (70004, 43602),
        (10662, 78376)
    ]
    for test in tests:
        first = test[0]
        second = test[1]
        print("\nx={},y={}".format(first, second))

        print("Start Euclidean GCD")
        start = datetime.datetime.now()
        gcd = gcd_euclidean(first, second)
        end = datetime.datetime.now()
        print("Time elapsed: {}".format(end - start))
        print("Gcd is {}\n".format(gcd))

        print("Start Prime Factorization GCD")
        start = datetime.datetime.now()
        gcd = gcd_prime_factors(first, second)
        end = datetime.datetime.now()
        print("Time elapsed: {}".format(end - start))
        print("Gcd is {}\n".format(gcd))

        print("Start Brute Force GCD")
        start = datetime.datetime.now()
        gcd = gcd_brute_force(first, second)
        end = datetime.datetime.now()
        print("Time elapsed: {}".format(end - start))
        print("Gcd is {}\n".format(gcd))
