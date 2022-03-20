#
# Write the implementation for A3 in this file
"""
Requirements:
    1. You will be given one of the problems below to solve
    2. Use procedural programing and the simple feature-driven software development process
    3. Provide a console-based user interface that accepts given commands exactly as required
    4. Use built-in compound types to represent entities in the problem domain and access them using getter and setter
    functions
    5. Have at least 10 items in your application at startup
    6. Provide specification and tests for all non-UI functions related to every functionality

Apartment Building Administrator
Jane is the administrator of an apartment building and she wants to manage the monthly expenses for each apartment.
Each expense is stored using the following elements: apartment (number of apartment, positive integer), amount (positive
integer), type (from one of the predefined categories water, heating, electricity, gas and other). Write a program that
implements the functionalities exemplified below:
(A) Add new transaction
    add <apartment> <type> <amount>
    e.g.
    add 25 gas 100 – add to apartment 25 an expense for gas in amount of 100 RON
(B) Modify expenses
    remove <apartment>
    remove <start apartment> to <end apartment>
    remove <type>
    replace <apartment> <type> with <amount>
    e.g.
    remove 15 – remove all expenses for apartment 15
    remove 5 to 10 – remove all expenses for apartments between 5 and 10
    remove gas – remove all gas expenses from all apartments
    replace 12 gas with 200 – replace the amount of the expense with type gas for apartment 12 with 200 RON\
(C) Display expenses having different properties
    list
    list <apartment>
    list [ < | = | > ] <amount>
    e.g.
    list – display all expenses
    list 15 – display all expenses for apartment 15
    list > 100 - display all apartments having total expenses >100 RON
    list = 17 - display all apartments having total expenses =17 RON
"""


#

#
# domain section is here (domain = numbers, transactions, expenses, etc.)
# getters / setters
# No print or input statements in this section
# Specification for all non-trivial functions (trivial usually means a one-liner)


def create_expense(apartment_number, expense_type, expense_amount):
    """
    Create an expense for an apartment with given attributes
    :param apartment_number: The apartment's number
    :param expense_type: The expense's type
    :param expense_amount: The amount of the expense, int
    :return: The new expense for a given apartment, or None if could not be created
    """
    type_list = ['water', 'heating', 'electricity', 'gas', 'other']
    if expense_type not in type_list:
        raise ValueError("Invalid expense!")
    return {'apartment': apartment_number, 'type': expense_type, 'amount': expense_amount}


def get_apartment_number(expense):
    return expense['apartment']


def get_expense_type(expense):
    return expense['type']


def get_expense_amount(expense):
    return expense['amount']


def set_apartment_number(expense_list, apartment):
    expense_list['apartment'] = apartment


def set_expense_type(expense_list, type):
    expense_list['type'] = type


def set_expense_amount(expense_list, amount):
    expense_list['amount'] = amount


def to_str(expense):
    """
    Turns into str the list of the expenses
    :param expense: -
    :return: the str of the expense
    """
    return 'apartment' + str(get_apartment_number(expense)).rjust(3) + ',' + str(get_expense_type(expense)) + ',' \
           + str(get_expense_amount(expense))


# Functionalities section (functions that implement required features)
# No print or input statements in this section
# Specification for all non-trivial functions (trivial usually means a one-liner)
# Each function does one thing only
# Functions communicate using input parameters and their return values

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
            expense_sum = expense_sum + get_expense_amount(expense_list[index])
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


def add_expense(expense_list, expense):
    """
    This function adds an expense to the initial list of expenses
    :param expense_list: the list of expenses
    :param expense: the expense we are looking forward to add
    :return: -
    """
    if find_by_apartment_number(expense_list, get_apartment_number(expense)) > -1:
        if find_by_expense_type(expense_list, get_expense_type(expense)) != -1:
            raise ValueError('Duplicate expense!')
    expense_list.append(expense)


def remove_expense_apartment_or_type(expense_list, parameter):
    """
    function to remove an expense by the number of the apartment or by the type of the expense
    :param expense_list: the list of expenses
    :param parameter: the parameter from the user-command
    :return: True if expense is removed, False if otherwise
    """
    to_remove = str(parameter)
    found_expense = False
    for index in expense_list:
        if str(to_remove) == str(get_apartment_number(index)) or str(to_remove) == get_expense_type(index):
            found_expense = True
            expense_list.remove(index)
    return found_expense


def remove_expense_start_to_end(expense_list, start, end):
    """
    Function to remove the expenses of the apartments between start apartment and end apartment
    :param expense_list: the list of the expenses
    :param start: the start apartment
    :param end: the end apartment
    :return: True if expenses are removed, false otherwise
    """
    list_to_remove = list(range(start, end + 1))
    expense_found = False
    for current_apartment in list_to_remove:
        for index in expense_list:
            if str(current_apartment) == str(get_apartment_number(index)):
                expense_list.remove(index)
                current_apartment += 1
                expense_found = True
    return expense_found


def replace_expense_amount(expense_list, apartment_number, expense_type, expense_amount):
    """
    function to replace the expense amount of an expense for an apartment
    :param expense_list: the list of all the expenses
    :param apartment_number: the number of the apartment
    :param expense_type: the type of the expense
    :param expense_amount: the amount of the expense to replace
    :return: True if expense is replaced, False otherwise
    """
    expense_found = False
    for index in expense_list:
        if apartment_number == str(get_apartment_number(index)) and expense_type == str(get_expense_type(index)):
            index['amount'] = expense_amount
            expense_found = True
    return expense_found


# UI section
# (all functions that have input or print statements, or that CALL functions with print / input are  here).
# Ideally, this section should not contain any calculations relevant to program functionalities


def split_command(command):
    """
    Divide user command into command word and command params
    :param command: user command
    :return: command word, params
    """
    tokens = command.strip().split(' ', 1)
    tokens[0] = tokens[0].strip().lower()
    return tokens[0], '' if len(tokens) == 1 else tokens[1].strip()


def add_expense_command_ui(expense_list, command_params):
    tokens = command_params.split()
    if len(tokens) != 3:
        raise ValueError('Invalid param count to create expense!')

    apartment_number = tokens[0].strip()
    expense_type = tokens[1].strip()
    expense_amount = int(tokens[2].strip())
    expense = create_expense(apartment_number, expense_type, expense_amount)
    add_expense(expense_list, expense)


def remove_expense_command_ui(expense_list, command_params):
    params = command_params.split()
    if len(params) == 1 or len(params) == 3:
        if len(params) == 1:
            parameter = str(params[0].strip())
            expense_found = remove_expense_apartment_or_type(expense_list, parameter)
            if not expense_found:
                raise ValueError("Expense not found!")
            else:
                print("Removed the solicited expense!")
        elif len(params) == 3:
            start = int(params[0].strip())
            end = int(params[2].strip())
            if params[1].strip() == "to":
                expense_found = remove_expense_start_to_end(expense_list, start, end)
                if not expense_found:
                    raise ValueError("None of the expenses given exist!")
                else:
                    print("Removed the solicited expenses!")
            else:
                raise ValueError("Invalid parameters!")
    else:
        raise ValueError("Invalid number of parameters!")


def replace_expense_command_ui(expense_list, command_params):
    params = command_params.split()
    if len(params) != 4:
        raise ValueError("Invalid number of parameters!")
    else:
        apartment_number = str(params[0].strip())
        expense_type = str(params[1].strip())
        expense_amount = str(params[3].strip())
        if params[2].strip() == "with":
            expense_found = replace_expense_amount(expense_list, apartment_number, expense_type, expense_amount)
            if not expense_found:
                raise ValueError("The expense doesn't exist!")
            else:
                print("Expense replaced successfully!")
        else:
            raise ValueError("Invalid parameters!")


def display_expense_command_ui(expense_list, command_params):
    params = command_params.split()
    if len(params) == 0:
        for expense in expense_list:
            print(to_str(expense))
    elif len(params) == 1:
        for expense in get_expenses_by_apartment_number(expense_list, params[0]):
            print(to_str(expense))
    elif len(params) == 2:
        for apartment in get_apartments_by_total_expense_sum(expense_list, params[0], int(params[1])):
            print(apartment)


def print_menu():
    print("Choose a command: ")
    print("add <apartment> <type> <amount>")
    print("remove <apartment>")
    print("remove <start apartment> to <end apartment>")
    print("remove <type>")
    print("replace <apartment> <type> with <amount>")
    print("list")
    print("list <apartment>")
    print("list [<|=|>] <amount>")
    print("exit")


def start_command_ui():
    print_menu()
    expense_list = []
    test_init(expense_list)
    command_dict = {'add': add_expense_command_ui, 'remove': remove_expense_command_ui,
                    'replace': replace_expense_command_ui, 'list': display_expense_command_ui}
    are_we_done_yet = False
    while not are_we_done_yet:
        command = input("command> ")
        command_word, command_params = split_command(command)
        if command_word in command_dict:
            try:
                command_dict[command_word](expense_list, command_params)
            except ValueError as ve:
                print(str(ve))
        elif 'exit' == command_word:
            are_we_done_yet = True
            print("Bye bye!")
        else:
            print("Bad command!")


# Test functions go here
#
# Test functions:
#   - no print / input
#   - great friends with assert


def test_init(test_list):
    # use this function to add the 10 required items
    # use it to set up test data
    test_list.append(create_expense('1', 'water', 100))
    test_list.append(create_expense('2', 'heating', 58))
    test_list.append(create_expense('3', 'electricity', 154))
    test_list.append(create_expense('4', 'gas', 20))
    test_list.append(create_expense('5', 'other', 12))
    test_list.append(create_expense('6', 'water', 87))
    test_list.append(create_expense('7', 'heating', 2))
    test_list.append(create_expense('8', 'electricity', 9))
    test_list.append(create_expense('9', 'gas', 31))
    test_list.append(create_expense('10', 'other', 23))


def test_split_command():
    cmd = '    aDd 100, water    , 5 '
    cmd_word, cmd_params = split_command(cmd)
    assert cmd_word == 'add'
    assert cmd_params == '100, water    , 5'

    cmd = 'eXit'
    cmd_word, cmd_params = split_command(cmd)
    assert cmd_word == 'exit'
    assert cmd_params == ''


# test_split_command()


def test_get_total_expenses_by_apartment_number():
    expense_list = [{'apartment': 1, 'type': "water", 'amount': 10},
                    {'apartment': 1, 'type': "gas", 'amount': 10}]
    apartment_number = 1
    assert get_total_expenses_by_apartment_number(expense_list, apartment_number) == 20


# test_get_total_expenses_by_apartment_number()


def test_get_expenses_by_apartment_number():
    expense_list = [{'apartment': 1, 'type': "water", 'amount': 10},
                    {'apartment': 2, 'type': "water", 'amount': 10}]
    apartment_number = 1
    assert get_expenses_by_apartment_number(expense_list, apartment_number) == \
           [{'apartment': 1, 'type': "water", 'amount': 10}]


# test_get_expenses_by_apartment_number()


def test_get_apartments_by_total_expense_sum():
    expense_list = [{'apartment': 1, 'type': "gas", 'amount': 2},
                    {'apartment': 1, 'type': "other", 'amount': 5},
                    {'apartment': 2, 'type': "gas", 'amount': 10},
                    {'apartment': 3, 'type': "gas", 'amount': 20}]
    sign = '='
    total_sum = 7
    assert get_apartments_by_total_expense_sum(expense_list, sign, total_sum) == [1]


# test_get_apartments_by_total_expense_sum()


def test_find_by_apartment_number():
    expense_list = [{'apartment': 1, 'type': "water", 'amount': 10},
                    {'apartment': 2, 'type': "water", 'amount': 10}]
    apartment_number = 1
    assert find_by_apartment_number(expense_list, apartment_number) == 0


# test_find_by_apartment_number()


def test_find_by_expense_type():
    expense_list = [{'apartment': 1, 'type': "water", 'amount': 10}]
    expense_type = "water"
    assert find_by_expense_type(expense_list, expense_type) == 0


# test_find_by_expense_type()


def test_remove_expense_apartment_or_type():
    expense_list = [{'apartment': 1, 'type': "water", 'amount': 10}]
    parameter = 1
    assert remove_expense_apartment_or_type(expense_list, parameter) == True


# test_remove_expense_apartment_or_type()


def test_remove_expense_start_to_end():
    expense_list = [{'apartment': 1, 'type': "water", 'amount': 10}, {'apartment': 2, 'type': "water", 'amount': 10}]
    start = 1
    end = 2
    assert remove_expense_start_to_end(expense_list, start, end) == True


# test_remove_expense_start_to_end()


def test_replace_expense_amount():
    expense_list = [{'apartment': 1, 'type': "water", 'amount': 10}]
    apartment_number = "1"
    expense_type = "water"
    expense_amount = 20
    assert replace_expense_amount(expense_list, apartment_number, expense_type, expense_amount) == True


# test_replace_expense_amount()


start_command_ui()
