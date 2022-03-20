"""
This is the user interface module. These functions call functions from the domain and functions module.
"""

from src.functions.functions import *
from src.domain.entity import *


def split_command(command):
    """
    Divide user command into command word and command params
    :param command: user command
    :return: command word, params
    """
    params = command.strip().split(' ', 1)
    params[0] = params[0].strip().lower()
    return params[0], '' if len(params) == 1 else params[1].strip()


def add_expense_command_ui(expense_list, command_params, history):
    params = command_params.split()
    if len(params) != 3:
        raise ValueError('Invalid param count to create expense!')

    apartment_number = params[0].strip()
    expense_type = params[1].strip()
    expense_amount = int(params[2].strip())
    add_expense(expense_list, apartment_number, expense_type, expense_amount, history)


def remove_expense_command_ui(expense_list, command_params, history):
    params = command_params.split()
    if len(params) == 1 or len(params) == 3:
        if len(params) == 1:
            parameter = str(params[0].strip())
            expense_found = remove_expense_apartment_or_type(expense_list, parameter, history)
            if not expense_found:
                raise ValueError("Expense not found!")
            else:
                print("Removed the solicited expense!")
        elif len(params) == 3:
            start = int(params[0].strip())
            end = int(params[2].strip())
            if params[1].strip() == "to":
                expense_found = remove_expense_start_to_end(expense_list, start, end, history)
                if not expense_found:
                    raise ValueError("None of the expenses given exist!")
                else:
                    print("Removed the solicited expenses!")
            else:
                raise ValueError("Invalid parameters!")
    else:
        raise ValueError("Invalid number of parameters!")


def replace_expense_command_ui(expense_list, command_params, history):
    params = command_params.split()
    if len(params) != 4:
        raise ValueError("Invalid number of parameters!")
    else:
        apartment_number = str(params[0].strip())
        expense_type = str(params[1].strip())
        expense_amount = str(params[3].strip())
        if params[2].strip() == "with":
            expense_found = replace_expense_amount(expense_list, apartment_number, expense_type, expense_amount, history)
            if not expense_found:
                raise ValueError("The expense doesn't exist!")
            else:
                print("Expense replaced successfully!")
        else:
            raise ValueError("Invalid parameters!")


def display_expense_command_ui(expense_list, command_params, history):
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


def sum_expense_command_ui(expense_list, command_params, history):
    params = command_params.split()
    if len(params) == 0:
        raise ValueError("No params for the command!")
    elif len(params) == 1:
        parameter = str(params[0].strip())
        sum = sum_expense_by_expense_type(expense_list, parameter)
        print(sum)
    elif len(params) > 1:
        raise ValueError("Too many parameters!")


def display_max_amount_ui(expense_list, command_params, history):
    params = command_params.split()
    if len(params) == 0:
        raise ValueError("No apartment to display the maximum amount!")
    elif len(params) == 1:
        parameter = params[0].strip()
        maximum, type = max_amount(expense_list, parameter)
        print("The maximum amount for ap " + str(parameter) + " is " + str(maximum) + " for " + str(type))


def sort_expense_command_ui(expense_list, command_params, history):
    params = command_params.split()
    if len(params) == 0:
        raise ValueError("Don't know by what to sort the list!")
    elif len(params) == 1:
        parameter = str(params[0].strip())
        if parameter == 'apartment':
            for apartment in sort_expense_by_apartment_or_type(expense_list, parameter):
                print(apartment)
        elif parameter == 'type':
            for type in sort_expense_by_apartment_or_type(expense_list, parameter):
                print(type)


def filter_expense_command_ui(expense_list, command_params, history):
    params = command_params.split()
    if len(params) == 0:
        raise ValueError("Don't know by what to filter the list!")
    elif len(params) == 1:
        parameter = str(params[0].strip())
        filter_expense_by_type_or_value(expense_list, parameter, history)


def undo_command_ui(expense_list, command_params, history):
    undo_command(expense_list, command_params, history)


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
    print("sum <type>")
    print("max <apartment>")
    print("sort apartment")
    print("sort type")
    print("filter <type>")
    print("filter <value>")
    print("undo")
    print("exit")


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


def start_command_ui():
    print_menu()
    expense_list = []
    history = []
    test_init(expense_list)
    command_dict = {'add': add_expense_command_ui, 'remove': remove_expense_command_ui,
                    'replace': replace_expense_command_ui, 'list': display_expense_command_ui,
                    'sum': sum_expense_command_ui, 'max': display_max_amount_ui, 'sort': sort_expense_command_ui,
                    'filter': filter_expense_command_ui, 'undo': undo_command_ui}
    are_we_done_yet = False
    while not are_we_done_yet:
        command = input("command> ")
        command_word, command_params = split_command(command)
        if command_word in command_dict:
            try:
                command_dict[command_word](expense_list, command_params, history)
            except ValueError as ve:
                print(str(ve))
        elif 'exit' == command_word:
            are_we_done_yet = True
            print("Bye bye!")
        else:
            print("Bad command!")


"""
Tests
"""


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
