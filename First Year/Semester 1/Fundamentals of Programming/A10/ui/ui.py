"""
UI module for the UI class
Only ui methods, with input and output
"""
from datetime import date
from src.exceptions import StudentException, AssignmentException, UndoRedoException
from src.repository.repo import RepositoryException


class UI:
    def __init__(self, student_service, assignment_service, grade_service, statistics, undo_redo_service):
        self.student_service = student_service
        self.assignment_service = assignment_service
        self.grade_service = grade_service
        self.statistics = statistics
        self.undo_redo_service = undo_redo_service

    def add_student_ui(self):
        student_id = input("Enter student id: ")
        name = input("Enter name: ")
        group = input("Enter group: ")
        self.student_service.add(student_id, name, group)

    def remove_student_ui(self):
        student_id = input("Enter student id to remove: ")
        self.student_service.remove(student_id)
        self.grade_service.remove_by_student(student_id)

    def update_student_ui(self):
        student_id = input("Enter student id to update: ")
        new_name = input("Enter new name: ")
        new_group = int(input("Enter new group: "))
        self.student_service.update(student_id, new_name, new_group)

    def list_students_ui(self):
        students = self.student_service.get_all()
        if len(students) == 0:
            print("There are no students!")
        for student in students:
            print(str(student))

    def add_assignment_ui(self):
        assignment_id = input("Enter assignment id: ")
        description = input("Enter description: ")
        deadline_year = int(input("Enter year: "))
        deadline_month = int(input("Enter month: "))
        deadline_day = int(input("Enter day: "))
        deadline = date(deadline_year, deadline_month, deadline_day)
        self.assignment_service.add(assignment_id, description, deadline)

    def remove_assignment_ui(self):
        assignment_id = input("Enter assignment id to remove: ")
        self.assignment_service.remove(assignment_id)
        self.grade_service.remove_by_assignment(assignment_id)

    def update_assignment_ui(self):
        assignment_id = input("Enter assignment id to update: ")
        new_description = input("Enter new description: ")
        deadline_year = int(input("Enter new year: "))
        deadline_month = int(input("Enter new month: "))
        deadline_day = int(input("Enter new day: "))
        new_deadline = date(deadline_year, deadline_month, deadline_day)
        self.assignment_service.update(assignment_id, new_description, new_deadline)

    def list_assignment_ui(self):
        assignments = self.assignment_service.get_all()
        if len(assignments) == 0:
            print("There are no assignments!")
        for assignment in assignments:
            print(str(assignment))

    def assign_to_student_s_ui(self):
        print("LIST OF STUDENTS IDS: ")
        students = self.student_service.get_all()
        student_ids = []
        for index in range(len(students)):
            student_ids.append(students[index].student_id)
        for id_ in student_ids:
            print(str(id_))
        print("LIST OF ASSIGNMENTS IDS: ")
        assignments = self.assignment_service.get_all()
        assignment_ids = []
        for index in range(len(assignments)):
            assignment_ids.append(assignments[index].assignment_id)
        for id_ in assignment_ids:
            print(str(id_))
        assignment_id = input("What assignment do you want to give? Enter the id: ")
        student_id = input("Enter the id of the student: ")
        if student_id in student_ids:
            if assignment_id in assignment_ids:
                self.grade_service.add(student_id, assignment_id, 0)
                print("Successfully assigned!")
            else:
                raise RepositoryException("No such assignment id in the list!")
        else:
            raise RepositoryException("No such student id in the list!")

    def list_assigned_ui(self):
        grades = self.grade_service.get_all()
        if len(grades) == 0:
            raise RepositoryException("The list of given assignments is empty!")
        for grade in grades:
            print(str(grade))

    def remove_assigned_ui(self):
        students = self.student_service.get_all()
        student_ids = []
        for index in range(len(students)):
            student_ids.append(students[index].student_id)
        assignments = self.assignment_service.get_all()
        assignment_ids = []
        for index in range(len(assignments)):
            assignment_ids.append(assignments[index].assignment_id)
        student_id = input("Enter the id of the student: ")
        assignment_id = input("What assignment do you want to remove? Enter the id: ")
        if student_id in student_ids:
            if assignment_id in assignment_ids:
                self.grade_service.remove(student_id, assignment_id)
            else:
                raise RepositoryException("No such assignment id in the list!")
        else:
            raise RepositoryException("No such student id in the list!")

    @staticmethod
    def unique(list_):
        list_set = set(list_)
        unique_list = (list(list_set))
        return unique_list

    def grade_assignment_ui(self):
        grades = self.grade_service.get_all()
        students = []
        print("The students that have assignments are: ")
        for index in range(len(grades)):
            students.append(grades[index].student_id)
        unique_students = self.unique(students)
        if len(unique_students) == 0:
            raise RepositoryException("No student with assignments.")
        for index in range(len(unique_students)):
            print(unique_students[index])
        student_id = input("Enter the student you want to grade: ")
        if student_id not in unique_students:
            raise RepositoryException("Invalid student id, there's no student with this id with assignments!")
        else:
            assignments = []
            grade_type = []
            print("This student has the following assignments: ")
            for index in range((len(grades))):
                if grades[index].student_id == student_id:
                    if grades[index].grade == 0:
                        assignments.append(grades[index].assignment_id)
                        grade_type.append({'assignment': grades[index].assignment_id, 'status': "ungraded"})
                    else:
                        assignments.append(grades[index].assignment_id)
                        grade_type.append({'assignment': grades[index].assignment_id, 'status': "graded"})
            for index in range(len(assignments)):
                print(assignments[index] + ", " + grade_type[index]['status'])
            assignment_id = input("Enter the id of the assignment you want to grade: ")
            if assignment_id in assignments:
                for index_type in range(len(grade_type)):
                    if grade_type[index_type]['assignment'] == assignment_id:
                        if grade_type[index_type]['status'] == "graded":
                            raise RepositoryException("This assignment has already been graded.")
                grade = input("Enter the grade: ")
                if grade == '':
                    raise ValueError("Grade input is empty.")
                self.grade_service.grade(student_id, assignment_id, grade)
            else:
                raise RepositoryException("Invalid id, there's no student id with the provided assignment!")
            for index in range(len(grade_type)):
                for index1 in range(len(grades)):
                    if grades[index1].assignment_id == grade_type[index]['assignment']:
                        if grades[index1].grade == 0:
                            grade_type[index]['status'] = "ungraded"
                        else:
                            grade_type[index]['status'] = "graded"

    def statistics_1_ui(self):
        print("--All students who received a given assignment, ordered by average grade for that assignment--")
        unique_assignments = self.statistics.get_unique_assignments()
        for index in range(len(unique_assignments)):
            print("ASSIGNMENT: {}".format(unique_assignments[index]))
            print("STUDENT ID ---------- GRADE")
            unique_students = self.statistics.statistics_1(unique_assignments[index])
            for index1 in range(len(unique_students)):
                if unique_students[index1][1] != 0:
                    print(unique_students[index1][0] + "     ----------   " + str(unique_students[index1][1]))
                elif unique_students[index1][1] == 0:
                    print(unique_students[index1][0] + "     ---------- ungraded")

    def statistics_2_ui(self):
        print("--All students who are late in handing in at least one assignment--")
        unique_late_students_all = self.statistics.statistics_2()
        if len(unique_late_students_all) != 0:
            for index in range(len(unique_late_students_all)):
                print(unique_late_students_all[index])
        else:
            print("No students that are late for all the given assignments.")

    def statistics_3_ui(self):
        print("--Students with the best school situation, "
              "sorted in descending order of the average grade received for all assignments--")
        best_students = self.statistics.statistics_3()
        for index in range(len(best_students)):
            if best_students[index][1] != 0:
                print("Student ID: {}, average grade: {}".format(best_students[index][0], best_students[index][1]))
            else:
                print("Student ID: {}, this student is late for all assignments, average grade is 0.".format(best_students[index][0]))

    def passing_grades_sorted_ui(self):
        print("--Grades >= 5--")
        passing_grades_sorted = self.grade_service.filter_by_grade()
        for index in range(len(passing_grades_sorted)):
            print(str(passing_grades_sorted[index]))

    def show_menu_ui(self):
        print("OPTIONS: ")
        print("0. Exit.")
        print("1. Add a/an student/assignment.")
        print("2. Remove a/an student/assignment.")
        print("3. Update a/an student/assignment.")
        print("4. List all students/assignments.")
        print("5. Assign an assignment to a student.")
        print("6. List all the given assignments and grades.")
        print("7. Remove an assigned assignment.")
        print("8. Grade an assignment.")
        print("9. STATISTICS")
        print("10.UNDO")
        print("11.REDO")
        print("12.List all the grades >= 5, sorted by grade.")

    def submenu_1_ui(self):
        print("OPTIONS: ")
        print("1. Add a student.")
        print("2. Add an assignment.")

    def submenu_2_ui(self):
        print("OPTIONS: ")
        print("1. Remove a student.")
        print("2. Remove an assignment.")

    def submenu_3_ui(self):
        print("OPTIONS: ")
        print("1. Update a student.")
        print("2. Update an assignment.")

    def submenu_4_ui(self):
        print("OPTIONS: ")
        print("1. List all students.")
        print("2. List all assignments.")

    def submenu_9_ui(self):
        print("OPTIONS: ")
        print("1. List all students who received a given assignment, ordered by average grade for that assignment.")
        print("2. List all students who are late in handing in at least one assignment."
              "\n   These are all the students who have an ungraded assignment for which the deadline has passed.")
        print("3. List students with the best school situation, "
              "sorted in descending order of the average grade received for all assignments.")

    def start(self):
        done = False
        while not done:
            try:
                self.show_menu_ui()
                option = int(input("Enter option: "))
                if option == 0:
                    done = True
                    print("Bye, bye!")
                elif option == 1:
                    self.submenu_1_ui()
                    option_1 = int(input("Enter option: "))
                    if option_1 == 1:
                        self.add_student_ui()
                    elif option_1 == 2:
                        self.add_assignment_ui()
                    else:
                        print("Bad input!")
                elif option == 2:
                    self.submenu_2_ui()
                    option_2 = int(input("Enter option: "))
                    if option_2 == 1:
                        self.remove_student_ui()
                    elif option_2 == 2:
                        self.remove_assignment_ui()
                    else:
                        print("Bad input!")
                elif option == 3:
                    self.submenu_3_ui()
                    option_3 = int(input("Enter option: "))
                    if option_3 == 1:
                        self.update_student_ui()
                    elif option_3 == 2:
                        self.update_assignment_ui()
                    else:
                        print("Bad input!")
                elif option == 4:
                    self.submenu_4_ui()
                    option_4 = int(input("Enter option: "))
                    if option_4 == 1:
                        self.list_students_ui()
                    elif option_4 == 2:
                        self.list_assignment_ui()
                elif option == 5:
                    self.assign_to_student_s_ui()
                elif option == 6:
                    self.list_assigned_ui()
                elif option == 7:
                    self.remove_assigned_ui()
                elif option == 8:
                    self.grade_assignment_ui()
                elif option == 9:
                    self.submenu_9_ui()
                    option_9 = int(input("Enter option: "))
                    if option_9 == 1:
                        self.statistics_1_ui()
                    elif option_9 == 2:
                        self.statistics_2_ui()
                    elif option_9 == 3:
                        self.statistics_3_ui()
                    else:
                        print("Bad input!")
                elif option == 10:
                    self.undo_redo_service.undo()
                elif option == 11:
                    self.undo_redo_service.redo()
                elif option == 12:
                    self.passing_grades_sorted_ui()
                else:
                    print("Bad input!")
            except RepositoryException as re:
                print(re)
            except StudentException as se:
                print(se)
            except AssignmentException as ae:
                print(ae)
            except ValueError as ve:
                print(ve)
            except UndoRedoException as ure:
                print(ure)
