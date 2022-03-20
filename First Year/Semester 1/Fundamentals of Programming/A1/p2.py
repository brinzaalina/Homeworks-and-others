#
# Implement the program to solve the problem statement from the second set here
#
def find_smallest_fibo_greater_than(n):
    first = 1
    second = 1
    third = 1
    while third <= n:
        third = first + second
        first = second
        second = third
    return third


n = int(input("Give a natural number: "))
m = find_smallest_fibo_greater_than(n)
print("The smallest number from the Fibonacci sequence larger than", n, "is", m)
