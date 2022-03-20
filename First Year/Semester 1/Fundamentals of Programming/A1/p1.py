#
# Implement the program to solve the problem statement from the first set here
#
def prime(val):
    for divisor in range(2, val):
        if val % divisor == 0:
            return False
    return True


def determine_primes(n):
    for p1 in range(2, n - 1):
        if prime(p1) and prime(n - p1):
            return p1, n - p1
    return -1, -1


n = int(input("Give a natural number: "))
p1, p2 = determine_primes(n)
if p1 == -1 and p2 == -1:
    print("No primes found!")
else:
    print("The prime numbers are", p1, "and", p2)
