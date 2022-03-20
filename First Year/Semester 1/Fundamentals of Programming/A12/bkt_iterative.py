"""
3.The sequence a = a1, ..., an with integer elements is given. Determine all strictly increasing subsequences of
sequence a (conserve the order of elements in the original sequence).. (Iterative implementation)
"""
import math


def check_increasing(subset_of_array):
    """
    Function to check if a subset is increasing or not.
    :param subset_of_array: The current subset.
    :return: True if it is increasing, False if otherwise.
    """
    if len(subset_of_array) == 1:
        return True
    else:
        increasing = True
        for index in range(len(subset_of_array)-1):
            if int(subset_of_array[index]) >= int(subset_of_array[index+1]):
                increasing = False
        return increasing


def is_consistent(subset_of_array, length):
    """
    Function to check if the subsequence is consistent.
    :param subset_of_array: the subsequence.
    :param length: the length of the array
    :return: True if consistent, False otherwise
    """
    return len(subset_of_array) < length and len(subset_of_array) != 0


def subset(array, length):
    """
    Function for finding all strictly increasing subsequences.
    :param array: the initial array
    :param length: the length of the array
    :return: a stack in which we store all the solutions
    """
    stack = []
    subset_of_array = []
    pow_set_size = int(math.pow(2, length))
    for counter in range(0, pow_set_size):
        subset_of_array.clear()
        for index in range(0, length):
            if (counter & (1 << index)) > 0:
                subset_of_array.append(array[index])
        if check_increasing(subset_of_array) is True and is_consistent(subset_of_array, len(array)):
            stack.append(subset_of_array[:])
    return stack


def subset_find_call(array):
    """
    In this function we initialize the call for de backtracking function.
    :param array: the array for which we need to find the subsequences.
    :return: -
    """
    stack = subset(array, len(array))
    stack.sort(key=lambda x: len(x))
    for index in range(len(stack)):
        print(*stack[index])


array = input("For what array do you want to find all strictly increasing subsets? Press 'e' to exit.\n")
while array != 'e':
    array = array.split(',')
    subset_find_call(array)
    array = input("For what array do you want to find all strictly increasing subsets? Press 'e' to exit.\n")