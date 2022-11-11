# 9. Algorithm for determining all bases b with respect to which a composite odd number n is strong
# pseudoprime. Use the repeated squaring modular exponentiation method.


def repeated_squaring_modular_exponentiation(base, exponent, modulus):
    # compute the remainder of base^exponent divided by modulus
    if modulus == 1:
        return 0
    remainder = 1
    base = base % modulus
    while exponent > 0:
        if exponent % 2 == 1:
            remainder = (remainder * base) % modulus  # remainder is multiplied by base and we get the new remainder
        exponent = exponent >> 1  # use bit shifting
        base = (base * base) % modulus  # continue squaring
    return remainder


# n = 2^s * t
def get_decomposition(n):
    s = 0
    t = 0
    while n % 2 == 0:
        s += 1
        n = n // 2
    t = n
    return s, t


def miller_rabin_test(n, base, s, t):
    # We compute the sequence base^t, base^(2t), ..., base^(2^s * t)
    # the number is pseudoprime to the base if the first value in the sequence is 1
    # or if the sequence contains 1 as a value, as the previous one should be -1 (n - 1)
    sequence = []
    for j in range(0, s + 1):
        sequence.append(repeated_squaring_modular_exponentiation(base, 2 ** j * t, n))
    if 1 in sequence:
        if sequence[0] == 1:
            return True
        else:
            position = sequence.index(1)
            if sequence[position - 1] == n - 1:
                return True
    return False


def test_bases(n):
    bases = []
    s, t = get_decomposition(n - 1)
    for i in range(2, n - 1):
        if miller_rabin_test(n, i, s, t):
            bases.append(i)
    return bases


def main():
    n = int(input("Enter odd composite number n: "))
    result = test_bases(n)
    if len(result) == 0:
        print("Number is not strong pseudoprime to any base")
    else:
        print("Number is strong pseudoprime to bases: ", result)


if __name__ == '__main__':
    main()
