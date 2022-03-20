"""
This is the repository, where we generate the first 10 elements of the list and where all the functionalities are really
implemented and executed
"""
from random import randint

from src.exceptions import RepositoryException


class RepositoryStudents:
    """
    The repository for students.
    """
    def __init__(self):
        """
        Here we generate the first 10 elements of the list of students and the list of students ids.
        """
        self._list_of_students = []

    def __len__(self):
        """
        -
        :return: The length of the list of students
        """
        return len(self._list_of_students)

    def clean_memory(self):
        self._list_of_students = []
        return self._list_of_students

    def add(self, new_student):
        """
        Repository method to add a new student to the list and the id of that student to the list of students ids.
        :param new_student: the new student
        :return: -
        """
        for student in self._list_of_students:
            if student.student_id == new_student.student_id:
                raise RepositoryException("Student already exists!")
        self._list_of_students.append(new_student)
        return new_student

    def remove(self, student_id):
        """
        Repository method to remove a student from the list and the id of the student from the list of ids
        :param student_id: the id of the student we want to remove
        :return: -
        """
        if len(self._list_of_students) == 0:
            raise RepositoryException("The list of students is already empty!")
        student = self.get_student_by_id(student_id)
        if student is None:
            raise RepositoryException("This student doesn't exist!")
        self._list_of_students.remove(student)
        return student

    def update(self, student_id, new_name, new_group):
        """
        Repository method to update a student from the list
        """
        searched_student = self.get_student_by_id(student_id)
        if searched_student is None:
            raise RepositoryException("This student doesn't exist!")
        old_student_name = self.get_student_by_id(student_id).name
        old_group = self.get_student_by_id(student_id).group
        searched_student.name = new_name
        searched_student.group = new_group
        return old_student_name, old_group

    def search_student_id(self, student_id):
        for student in self._list_of_students:
            if student.student_id == student_id:
                return True
        return False

    def get_student_by_id(self, student_id):
        for student in self._list_of_students:
            if student.student_id == student_id:
                return student
        return None

    def get_random_id(self):
        return self._list_of_students[randint(0, len(self._list_of_students)-1)].student_id

    def get_all_students(self):
        """
        Repository method to get all the students from the list
        :return: A copy of the list of students
        """
        return self._list_of_students[:]


class RepositoryAssignments:
    """
    The repository for the assignments.
    """
    def __init__(self):
        """
        Here we generate the first 10 elements of the list of assignments and the list of their ids
        """
        self._list_of_assignments = []

    def __len__(self):
        """
        -
        :return: the length of the list of assignments
        """
        return len(self._list_of_assignments)

    def clean_memory(self):
        self._list_of_assignments = []
        return self._list_of_assignments

    def add(self, new_assignment):
        """
        Repository method to add a new assignment to the list and its id to the list of ids
        :param new_assignment: the new assignment
        :return: -
        """
        for assignment in self._list_of_assignments:
            if assignment.assignment_id == new_assignment.assignment_id:
                raise RepositoryException("Assignment already exists!")
        self._list_of_assignments.append(new_assignment)
        return new_assignment

    def remove(self, assignment_id):
        """
        Repository method to remove an assignment from the list and its id from the list of ids
        :param assignment_id: the id of the assignment we want to remove
        :return: -
        """
        searched_assignment = self.get_assignment_by_id(assignment_id)
        if len(self._list_of_assignments) == 0:
            raise RepositoryException("The list of assignments is already empty!")
        if searched_assignment is None:
            raise RepositoryException("This assignment does not exist!")
        self._list_of_assignments.remove(searched_assignment)
        return searched_assignment

    def update(self, assignment_id, new_description, new_deadline):
        """
        Repository method to update an assignment from the list
        """
        old_assignment = self.get_assignment_by_id(assignment_id)
        if old_assignment is None:
            raise RepositoryException("Assignment does not exist!")
        old_description = self.get_assignment_description(assignment_id)
        old_deadline = self.get_assignment_deadline(assignment_id)
        old_assignment.description = new_description
        old_assignment.deadline = new_deadline
        return old_description, old_deadline

    def search_assignment_id(self, assignment_id):
        for assignment in self._list_of_assignments[:]:
            if assignment.assignment_id == assignment_id:
                return True
        return False

    def get_assignment_by_id(self, assignment_id):
        for assignment in self._list_of_assignments[:]:
            if assignment.assignment_id == assignment_id:
                return assignment
        return None

    def get_assignment_description(self, assignment_id):
        for assignment in self._list_of_assignments:
            if assignment.assignment_id == assignment_id:
                return assignment.description

    def get_assignment_deadline(self, assignment_id):
        for assignment in self._list_of_assignments:
            if assignment.assignment_id == assignment_id:
                return assignment.deadline

    def get_random_id(self):
        return self._list_of_assignments[randint(0, len(self._list_of_assignments)-1)].assignment_id

    def get_all_assignments(self):
        """
        Repository method to get all the elements of the assignments list
        :return: A copy of the assignments list
        """
        return self._list_of_assignments[:]


class RepositoryGrade:
    """
    Repository class to store all the graded and ungraded assignments.
    """
    def __init__(self):
        """
        Empty list for storing the grades.
        """
        self._grade_list = []

    def __len__(self):
        """
        -
        :return: The length of the list
        """
        return len(self._grade_list)

    def clean_memory(self):
        self._grade_list = []
        return self._grade_list

    def add(self, new_grade):
        """
        Adds an ungraded assignment.
        :param new_grade: the assignment
        :return: -
        """
        for grade in self._grade_list:
            if grade.student_id == new_grade.student_id:
                if grade.assignment_id == new_grade.assignment_id:
                    raise RepositoryException("The assignment is already given to this student.")
        self._grade_list.append(new_grade)

    def remove(self, student_id, assignment_id):
        """
        Removes a grade from the list.
        :param student_id: id of the student
        :param assignment_id: id of the assignment
        :return: -
        """
        found = False
        for grade in self._grade_list:
            if grade.student_id == student_id:
                if grade.assignment_id == assignment_id:
                    self._grade_list.remove(grade)
                    found = True
                    return grade
        if found is False:
            raise RepositoryException("No such assignment given to this student!")


    def remove_by_student(self, student_id):
        """
        Remove a grade by student
        :param student_id: the id of the student
        :return: -
        """
        index = 0
        while index in range(len(self._grade_list)):
            if self._grade_list[index].student_id == student_id:
                del self._grade_list[index]
            else:
                index += 1

    def remove_by_assignment(self, assignment_id):
        """
        Remove a grade by assignment
        :param assignment_id: the id of the assignment
        :return: -
        """
        index = 0
        while index in range(len(self._grade_list)):
            if self._grade_list[index].assignment_id == assignment_id:
                del self._grade_list[index]
            else:
                index += 1

    def search_student_id(self, student_id):
        for grade in self._grade_list:
            if grade.student_id == student_id:
                return True
        return False

    def search_assignment_id(self, assignment_id):
        for grade in self._grade_list:
            if grade.assignment_id == assignment_id:
                return True
        return False

    def search_if_grade_exists(self, student_id, assignment_id):
        for grade in self._grade_list:
            if grade.student_id == student_id:
                if grade.assignment_id == assignment_id:
                    return True
                else:
                    return False

    def remove_last_grades(self, number_of_grades):
        for index in range(number_of_grades):
            last = self._grade_list.pop()

    def grade(self, student_id, assignment_id, grade):
        """
        Grade a previously ungraded assignment.
        :param student_id: the id of the student
        :param assignment_id: the id of the assignment
        :param grade: the grade
        :return: -
        """
        if int(grade) < 0:
            raise ValueError("Grade can't be negative.")
        elif int(grade) > 10:
            raise ValueError("Grade must be an integer between 1 and 10.")
        else:
            index = 0
            while index in range(len(self._grade_list)):
                if self._grade_list[index].student_id == student_id:
                    if self._grade_list[index].assignment_id == assignment_id:
                        if self._grade_list[index].grade == 0:
                            self._grade_list[index].grade = grade
                        elif grade == 0:
                            self._grade_list[index].grade = grade
                        else:
                            raise RepositoryException("This student has already been graded for this assignment.")
                index += 1

    def get_all_grades(self):
        """
        :return: Copy of the grade list.
        """
        return self._grade_list[:]
