#
# Implement the program to solve the problem statement from the third set here
#
def get_prime_divisors(val):
    if val == 1:
        return [1]
    current_divisor = 2
    prime_divisors = []
    while val != 1:
        if val % current_divisor == 0:
            while val % current_divisor == 0:
                val = val / current_divisor
            prime_divisors.append(current_divisor)

        if current_divisor == 2:
            current_divisor = 3
        else:
            current_divisor = current_divisor + 2
    return prime_divisors


def get_nth_term(index):
    current_number = 1
    while True:
        prime_divisors = get_prime_divisors(current_number)
        prime_divisors_counter = len(prime_divisors)
        if prime_divisors_counter < index:
            index = index - prime_divisors_counter
        else:
            return prime_divisors[index - 1]
        current_number = current_number + 1


n = int(input("The position of the element: "))
print("The", n, "-th element from the sequence is", get_nth_term(n))
