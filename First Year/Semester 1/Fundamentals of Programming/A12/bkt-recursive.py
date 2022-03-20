"""
3.The sequence a = a1, ..., an with integer elements is given. Determine all strictly increasing subsequences of
sequence a (conserve the order of elements in the original sequence). (Recursive implementation)
"""


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


def subset(array, subset_of_array, index):
    """
    Function for finding and printing all the increasing subsequences.
    :param array: The whole array.
    :param subset_of_array: A subset of the array.
    :param index: The position from which we consider the array.
    :return: -
    """
    for i in range(index, len(array)):
        subset_of_array.append(int(array[i]))
        if check_increasing(subset_of_array) is True and is_consistent(subset_of_array, len(array)):
            print(*subset_of_array)
            subset(array, subset_of_array, i + 1)
            subset_of_array.pop(-1)
        else:
            subset_of_array.pop(-1)
    return


def subset_find_call(array):
    """
    In this function we initialize the call for de backtracking function.
    :param array: the array for which we need to find the subsequences.
    :return: -
    """
    subset_of_array = []
    index = 0
    subset(array, subset_of_array, index)


array = input("For what array do you want to find all strictly increasing subsets? Press 'e' to exit.\n")
while array != 'e':
    array = array.split(',')
    subset_find_call(array)
    array = input("For what array do you want to find all strictly increasing subsets? Press 'e' to exit.\n")