"""
Domain file includes code for entity management
entity = number, transaction, expense etc.
"""


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
