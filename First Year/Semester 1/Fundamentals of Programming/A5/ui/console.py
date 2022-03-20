"""
    UI class.

    Calls between program modules
    ui -> service -> entity
    ui -> entity
"""
from src.domain.entity import NumberException


class Console:
    def __init__(self, service):
        self._service = service

    def _show_menu_ui(self):
        print("OPTIONS")
        print("1. Add a number.")
        print("2. Display the list of numbers.")
        print("3. Filter the list so that it contains only the numbers between indices <start> and <end>.")
        print("4. Undo the last operation that modified program data.")
        print("5. Exit")

    def start_ui(self):
        done = False
        while not done:
            try:
                self._show_menu_ui()
                command = input("Enter option: ")
                if command == "1":
                    number_string = input("Complex number: ")
                    real_part, imaginary_part = self._service.parse_number_string(number_string)
                    self._service.add(real_part, imaginary_part)
                elif command == "2":
                    numbers = self._service.get_all()
                    for number in numbers:
                        print(str(numbers.index(number)) + "." + str(number))
                elif command == "3":
                    start = int(input("Start number (to filter the list): "))
                    end = int(input("End number (to filter the list): "))
                    self._service.filter(start, end)
                elif command == "4":
                    self._service.undo()
                elif command == "5":
                    done = True
                    print("Bye, bye!")
                else:
                    print("Bad input!")
            except NumberException as ne:
                print(str(ne))
            except ValueError as ve:
                print(str(ve))
