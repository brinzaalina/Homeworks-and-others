"""
Functions that implement program features. They should call each other, or other functions from the domain
"""
from src.ui.console import *
from src.domain.entity import *


def get_total_expenses_by_apartment_number(expense_list, apartment_number):
    """
    Computes the total sum of the expenses for an apartment number
    :param expense_list: the list of all expenses
    :param apartment_number: the number of the apartment
    :return: the sum of the expenses for the given apartment
    """
    expense_sum = 0
    for index in range(len(expense_list)):
        if apartment_number == get_apartment_number(expense_list[index]):
            expense_sum = expense_sum + int(get_expense_amount(expense_list[index]))
    return expense_sum


def get_expenses_by_apartment_number(expense_list, apartment_number):
    """
    Finds the expenses for an apartment
    :param expense_list: the list of all the expenses
    :param apartment_number: the apartment's number
    :return: the list of the expenses for the given apartment
    """
    new_expense_list = []
    for index in range(len(expense_list)):
        if apartment_number == get_apartment_number(expense_list[index]):
            new_expense_list.append(expense_list[index])
    return new_expense_list


def get_apartments_by_total_expense_sum(expense_list, sign, total_sum):
    """
    Finds the apartments that correspond with the given user-command
    :param expense_list: the list of all the expenses
    :param sign: the sign from the command; can be <, = or >
    :param total_sum: the sum of all the expenses for an apartment
    :return: the list of all the apartments that have the property given by the user
    """
    apartments = []
    for index in range(len(expense_list)):
        apartments.append(get_apartment_number(expense_list[index]))
    apartments = set(apartments)
    good_apartments = []
    for apartment in apartments:
        expense_sum = get_total_expenses_by_apartment_number(expense_list, apartment)
        if sign == '=' and expense_sum == total_sum:
            good_apartments.append(apartment)
        elif sign == '<' and expense_sum < total_sum:
            good_apartments.append(apartment)
        elif sign == '>' and expense_sum > total_sum:
            good_apartments.append(apartment)
    return good_apartments


def find_by_apartment_number(expense_list, apartment_number):
    """
    Find the expense with the given apartment number
    :param expense_list: List of expenses
    :param apartment_number: this is the number (str) we are searching for
    :return: The index of the apartment in the list, -1 if apartment not found
    """
    for index in range(len(expense_list)):
        if apartment_number == get_apartment_number(expense_list[index]):
            return index
    return -1


def find_by_expense_type(expense_list, expense_type):
    """
    Find the expense with the given expense type
    :param expense_list: list of expenses
    :param expense_type: this is the type of expense we are searching for
    :return: The index of the apartment in the list, -1 if apartment not found
    """
    for index in range(len(expense_list)):
        if expense_type == get_expense_type(expense_list[index]):
            return index
        else:
            return -1


def add_expense(expense_list, apartment_number, expense_type, expense_amount, history):
    """
    Function to add an expense to the list
    :param expense_list: the list of all the expenses
    :param apartment_number: the number of the apartment for which we add the expense
    :param expense_type: the type of the expense
    :param expense_amount: the amount of the expense
    :param history: for the undo function
    :return: -
    """
    for index in expense_list:
        if apartment_number == str(get_apartment_number(index)):
            if expense_type == str(get_expense_type(index)):
                raise ValueError("Duplicate expense!")
    history.append(expense_list[:])
    expense_list.append(create_expense(apartment_number, expense_type, expense_amount))


def remove_expense_apartment_or_type(expense_list, parameter, history):
    """
    function to remove an expense by the number of the apartment or by the type of the expense
    :param expense_list: the list of expenses
    :param parameter: the parameter from the user-command
    :param history: for the undo function
    :return: True if expense is removed, False if otherwise
    """
    history.append(expense_list[:])
    to_remove = str(parameter)
    found_expense = False
    for index in expense_list:
        if str(to_remove) == str(get_apartment_number(index)) or str(to_remove) == get_expense_type(index):
            found_expense = True
            expense_list.remove(index)
    return found_expense


def remove_expense_start_to_end(expense_list, start, end, history):
    """
    Function to remove the expenses of the apartments between start apartment and end apartment
    :param expense_list: the list of the expenses
    :param start: the start apartment
    :param end: the end apartment
    :param history: for the undo function
    :return: True if expenses are removed, false otherwise
    """
    history.append(expense_list[:])
    list_to_remove = list(range(start, end + 1))
    expense_found = False
    for current_apartment in list_to_remove:
        for index in expense_list:
            if str(current_apartment) == str(get_apartment_number(index)):
                expense_list.remove(index)
                current_apartment += 1
                expense_found = True
    return expense_found


def replace_expense_amount(expense_list, apartment_number, expense_type, expense_amount, history):
    """
    function to replace the expense amount of an expense for an apartment
    :param expense_list: the list of all the expenses
    :param apartment_number: the number of the apartment
    :param expense_type: the type of the expense
    :param expense_amount: the amount of the expense to replace
    :param history: for the undo function
    :return: True if expense is replaced, False otherwise
    """
    history.append(expense_list[:])
    expense_found = False
    for index in expense_list:
        if apartment_number == str(get_apartment_number(index)) and expense_type == str(get_expense_type(index)):
            index['amount'] = expense_amount
            expense_found = True
    return expense_found


def sum_expense_by_expense_type(expense_list, parameter):
    """
    Computes the sum of all the expenses with the given type
    :param expense_list: the list of the expenses
    :param parameter: the type of the expense
    :return: the sum of the expenses
    """
    to_sum = str(parameter)
    sum = 0
    for index in expense_list:
        if str(to_sum) == get_expense_type(index):
            sum += int(index['amount'])
    return sum


def max_amount(expense_list, parameter):
    """
    Function to determine the maximum amount for an apartment from the expenses that apartment has
    :param expense_list: the list of the expenses
    :param parameter: the apartment
    :return: the maximum amount and the type of it
    """
    maximum = -1
    type = ''
    for index in expense_list:
        if index['apartment'] == parameter:
            for i in range(1, len(index), 1):
                if int(index['amount']) > maximum:
                    maximum = index['amount']
                    type = index['type']
        else:
            continue
    return maximum, type


def sorter(item):
    return item[1]


def sort_expense_by_apartment_or_type(expense_list, parameter):
    """
    Sorts the list of apartments ascending by total amount of expenses
    :param expense_list: the list of expenses
    :param parameter: apartment or type
    :return: the sorted list
    """
    if parameter == "apartment":
        total_expenses_per_apartment = {}
        for index in expense_list:
            total_expenses_per_apartment[index['apartment']] = 0
        for index in expense_list:
            total_expenses_per_apartment[index['apartment']] += index['amount']
        sorted_total_expenses_per_apartment = sorted(total_expenses_per_apartment.items(), key=lambda kv: kv[1])
        return sorted_total_expenses_per_apartment
    elif parameter == "type":
        sum_gas = 0
        sum_water = 0
        sum_heating = 0
        sum_electricity = 0
        sum_other = 0
        for index in expense_list:
            if get_expense_type(index) == "gas":
                sum_gas += index['amount']
            elif get_expense_type(index) == "water":
                sum_water += index['amount']
            elif get_expense_type(index) == "heating":
                sum_heating += index['amount']
            elif get_expense_type(index) == "electricity":
                sum_electricity += index['amount']
            elif get_expense_type(index) == "other":
                sum_other += index['amount']
        total_per_expense = [('gas', sum_gas),
                             ('water', sum_water),
                             ('heating', sum_heating),
                             ('electricity', sum_electricity),
                             ('other', sum_other)]
        sorted_total_per_expense = sorted(total_per_expense, key=sorter)
        return sorted_total_per_expense
    else:
        raise ValueError("Can't sort by the given command!")


def filter_expense_by_type_or_value(expense_list, parameter, history):
    """
    Function to filter the list of the expenses by a given type or value
    :param expense_list: the list of the expenses
    :param parameter: a type of expense or an amount of money
    :param history: for the undo function
    :return: -
    """
    to_filter = parameter
    if to_filter in ['gas', 'water', 'electricity', 'other', 'heating']:
        history.append(expense_list[:])
        for index in expense_list[::-1]:
            if index['type'] != str(to_filter):
                expense_list.remove(index)
    else:
        history.append(expense_list[:])
        for index in expense_list[::-1]:
            if index['amount'] >= int(to_filter):
                expense_list.remove(index)


def undo_command(expense_list, command_params, history):
    """
    Function to undo the last executed command that can be undone
    :param expense_list: the list of the expenses
    :param command_params: -
    :param history: the history of the expense_list
    :return: -
    """
    params = command_params.split()
    if history == []:
        raise ValueError("Cannot undo!")
    else:
        if len(params) == 0:
            expense_list.clear()
            last_expense_list = history.pop()
            for expense in last_expense_list:
                expense_list.append(expense)
        else:
            raise ValueError("Invalid command for the undo function!")


"""
Tests
"""


def test_get_total_expenses_by_apartment_number():
    expense_list = [{'apartment': 1, 'type': "water", 'amount': 10},
                    {'apartment': 1, 'type': "gas", 'amount': 10}]
    apartment_number = 1
    assert get_total_expenses_by_apartment_number(expense_list, apartment_number) == 20


def test_get_expenses_by_apartment_number():
    expense_list = [{'apartment': 1, 'type': "water", 'amount': 10},
                    {'apartment': 2, 'type': "water", 'amount': 10}]
    apartment_number = 1
    assert get_expenses_by_apartment_number(expense_list, apartment_number) == \
           [{'apartment': 1, 'type': "water", 'amount': 10}]


def test_get_apartments_by_total_expense_sum():
    expense_list = [{'apartment': 1, 'type': "gas", 'amount': 2},
                    {'apartment': 1, 'type': "other", 'amount': 5},
                    {'apartment': 2, 'type': "gas", 'amount': 10},
                    {'apartment': 3, 'type': "gas", 'amount': 20}]
    sign = '='
    total_sum = 7
    assert get_apartments_by_total_expense_sum(expense_list, sign, total_sum) == [1]


def test_find_by_apartment_number():
    expense_list = [{'apartment': 1, 'type': "water", 'amount': 10},
                    {'apartment': 2, 'type': "water", 'amount': 10}]
    apartment_number = 1
    assert find_by_apartment_number(expense_list, apartment_number) == 0


def test_find_by_expense_type():
    expense_list = [{'apartment': 1, 'type': "water", 'amount': 10}]
    expense_type = "water"
    assert find_by_expense_type(expense_list, expense_type) == 0


def test_remove_expense_apartment_or_type():
    expense_list = [{'apartment': 1, 'type': "water", 'amount': 10}]
    parameter = 1
    history = []
    assert remove_expense_apartment_or_type(expense_list, parameter, history) == True


def test_remove_expense_start_to_end():
    expense_list = [{'apartment': 1, 'type': "water", 'amount': 10}, {'apartment': 2, 'type': "water", 'amount': 10}]
    start = 1
    end = 2
    history = []
    assert remove_expense_start_to_end(expense_list, start, end, history) == True


def test_replace_expense_amount():
    expense_list = [{'apartment': 1, 'type': "water", 'amount': 10}]
    apartment_number = "1"
    expense_type = "water"
    expense_amount = 20
    history = []
    assert replace_expense_amount(expense_list, apartment_number, expense_type, expense_amount, history) == True


def test_sum_expense_by_expense_type():
    expense_list = [{'apartment': 1, 'type': "water", 'amount': 10}, {'apartment': 2, 'type': "water", 'amount': 10}]
    parameter = "water"
    assert sum_expense_by_expense_type(expense_list, parameter) == 20


def test_max_amount():
    expense_list = [{'apartment': 1, 'type': "water", 'amount': 10},
                    {'apartment': 1, 'type': "gas", 'amount': 20},
                    {'apartment': 1, 'type': "electricity", 'amount': 30},
                    {'apartment': 1, 'type': "heating", 'amount': 40},
                    {'apartment': 1, 'type': "other", 'amount': 50}]
    parameter = 1
    assert max_amount(expense_list, parameter) == 50


def test_sort_expense_by_apartment_or_type():
    expense_list = [{'apartment': 1, 'type': "water", 'amount': 10},
                    {'apartment': 1, 'type': "gas", 'amount': 10},
                    {'apartment': 2, 'type': "water", 'amount': 10}]
    parameter = "apartment"
    assert sort_expense_by_apartment_or_type(expense_list, parameter) == [(2, 10), (1, 20)]
    expense_list = [{'apartment': 1, 'type': "water", 'amount': 10},
                    {'apartment': 2, 'type': "water", 'amount': 10},
                    {'apartment': 3, 'type': "gas", 'amount': 5},
                    {'apartment': 4, 'type': "heating", 'amount': 21},
                    {'apartment': 5, 'type': "electricity", 'amount': 100},
                    {'apartment': 6, 'type': "other", 'amount': 76}]
    parameter = "type"
    assert sort_expense_by_apartment_or_type(expense_list, parameter) == [('gas', 5),
                                                                          ('water', 20),
                                                                          ('heating', 21),
                                                                          ('other', 76),
                                                                          ('electricity', 100)]


def test_filter_expense_by_type_or_value():
    expense_list = [{'apartment': 1, 'type': "water", 'amount': 10},
                    {'apartment': 2, 'type': "water", 'amount': 15},
                    {'apartment': 3, 'type': "gas", 'amount': 20},
                    {'apartment': 4, 'type': "water", 'amount': 40},
                    {'apartment': 5, 'type': "other", 'amount': 100}]
    parameter = "water"
    history = []
    filter_expense_by_type_or_value(expense_list, parameter, history)
    assert expense_list == [{'apartment': 1, 'type': 'water', 'amount': 10},
                            {'apartment': 2, 'type': 'water', 'amount': 15},
                            {'apartment': 4, 'type': 'water', 'amount': 40}]
    expense_list = [{'apartment': 1, 'type': "water", 'amount': 10},
                    {'apartment': 2, 'type': "water", 'amount': 15},
                    {'apartment': 3, 'type': "gas", 'amount': 20},
                    {'apartment': 4, 'type': "water", 'amount': 40},
                    {'apartment': 5, 'type': "other", 'amount': 100}]
    parameter = "30"
    filter_expense_by_type_or_value(expense_list, parameter, history)
    assert expense_list == [{'apartment': 1, 'type': 'water', 'amount': 10},
                            {'apartment': 2, 'type': 'water', 'amount': 15},
                            {'apartment': 3, 'type': 'gas', 'amount': 20}]


def test_undo_command():
    expense_list = [{'apartment': 1, 'type': "water", 'amount': 10},
                    {'apartment': 2, 'type': "water", 'amount': 15},
                    {'apartment': 3, 'type': "gas", 'amount': 20},
                    {'apartment': 4, 'type': "water", 'amount': 40},
                    {'apartment': 5, 'type': "other", 'amount': 100}]
    apartment_number = 6
    expense_type = "heating"
    expense_amount = 39
    history = []
    add_expense(expense_list, apartment_number, expense_type, expense_amount, history)
    assert expense_list == [{'apartment': 1, 'type': 'water', 'amount': 10},
                            {'apartment': 2, 'type': 'water', 'amount': 15},
                            {'apartment': 3, 'type': 'gas', 'amount': 20},
                            {'apartment': 4, 'type': 'water', 'amount': 40},
                            {'apartment': 5, 'type': 'other', 'amount': 100},
                            {'apartment': 6, 'type': 'heating', 'amount': 39}]
    command_params = ""
    undo_command(expense_list, command_params, history)
    assert expense_list == [{'apartment': 1, 'type': 'water', 'amount': 10},
                            {'apartment': 2, 'type': 'water', 'amount': 15},
                            {'apartment': 3, 'type': 'gas', 'amount': 20},
                            {'apartment': 4, 'type': 'water', 'amount': 40},
                            {'apartment': 5, 'type': 'other', 'amount': 100}]


# test_get_total_expenses_by_apartment_number()
# test_get_expenses_by_apartment_number()
# test_find_by_apartment_number()
# test_find_by_expense_type()
# test_remove_expense_apartment_or_type()
# test_remove_expense_start_to_end()
# test_replace_expense_amount()
# test_sum_expense_by_expense_type()
# test_max_amount()
# test_sort_expense_by_apartment_or_type()
# test_filter_expense_by_type_or_value()
# test_undo_command()
