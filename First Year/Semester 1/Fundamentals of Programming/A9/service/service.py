import random
import string
from datetime import date
from src.domain.domain import Student, Assignment, Grade
from src.repository.repo import RepositoryException
from src.services.undo_redo_service import FunctionCall, Operation


class StudentService:
    """
    Class for the student service, from which we call the repository methods.
    """
    def __init__(self, student_repo, student_validator, undo_redo_service, grade_service):
        """
        Initialize the parameters of the StudentService
        :param student_repo: The repository for students
        :param student_validator: The validator for a student
        """
        self._undo_redo_service = undo_redo_service
        self._student_repo = student_repo
        self._student_validator = student_validator
        self._grade_service = grade_service

    def add(self, student_id, name, group):
        """
        Service method to add a new student.
        :param student_id: the id of the student
        :param name: the name of the student
        :param group: the group from which the student is
        :return: -
        """
        student = self.add_without_record(student_id, name, group)
        undo_ = FunctionCall(self.remove_without_record, student.student_id)
        redo_ = FunctionCall(self.add_without_record, student.student_id, student.name, student.group)
        self._undo_redo_service.record(Operation(undo_, redo_))

    def add_without_record(self, student_id, name, group):
        student = Student(student_id, name, group)
        self._student_validator.validate(student)
        self._student_repo.add(student)
        return student

    def add_student_and_grades(self, student_id, name, group, list_of_grades):
        student = Student(student_id, name, group)
        self._student_validator.validate(student)
        self._student_repo.add(student)
        if list_of_grades is not None:
            for grade in list_of_grades:
                self._grade_service.add_grade_without_record(grade[0], grade[1], grade[2])

    def remove(self, student_id):
        """
        Service method to remove a student
        :param student_id: The id of the student we want to remove
        :return: -
        """
        student, list_of_grades = self.remove_without_record(student_id)
        undo_ = FunctionCall(self.add_student_and_grades, student.student_id, student.name, student.group,
                             list_of_grades)
        redo_ = FunctionCall(self.remove_without_record, student.student_id)
        self._undo_redo_service.record(Operation(undo_, redo_))

    def remove_without_record(self, student_id):
        check_student_id = Student(student_id, 'test name', 911)
        self._student_validator.validate(check_student_id)
        student = self._student_repo.remove(student_id)
        list_of_grades = self._grade_service.remove_by_student(student_id)
        return student, list_of_grades

    def update(self, student_id, new_name, new_group):
        """
        Service method to update a student
        :param student_id: The id of the student we want to update
        :param new_name: the new name (can be the same as the old one)
        :param new_group: the new group (can be the same as the old one)
        :return: -
        """
        old_student_name, old_group = self.update_without_record(student_id, new_name, new_group)
        undo_ = FunctionCall(self.update_without_record, student_id, old_student_name, old_group)
        redo_ = FunctionCall(self.update_without_record, student_id, new_name, new_group)
        self._undo_redo_service.record(Operation(undo_, redo_))

    def update_without_record(self, student_id, new_name, new_group):
        old_student_name, old_group = self._student_repo.update(student_id, new_name, new_group)
        return old_student_name, old_group

    def get_all(self):
        """
        Service method to get all the students
        :return: the list of students
        """
        return self._student_repo.get_all_students()

    @staticmethod
    def random_student_id(length):
        """
        Generates a random string for the student_id.
        :param length: the length of the string
        :return: the id of the student
        """
        letters_and_digits = string.ascii_letters + string.digits
        student_id = ''.join((random.choice(letters_and_digits) for index in range(length)))
        return student_id

    def initialise(self):
        name_list = ["Abney Lisa", "Macchio Emanuel Andreas", "Nieve Oconnell", "Leila Aguirre", "Ailish Clarkson", "Christie Patrick", "Maia Owens", "Lilli English", "Brittney Gardiner", "Sebastian Ewing",
                     "Elle May Pickett", "Maira Thorpe", "Katy Oreilly", "Veronika Crane", "Kaiya Roche", "Zoya Clayton", "Eugene Church", "Tevin Hamilton", "Cayden Cobb", "Rita Thompson"]
        for index in range(10):
            student_id = self.random_student_id(6)
            name = random.choice(name_list)
            group = random.randint(911, 917)
            self.add_without_record(student_id, name, group)

class AssignmentService:
    """
    Class for the Assignment service.
    """
    def __init__(self, assignment_repo, assignment_validator, undo_redo_service, grade_service):
        """
        Initialize the parameters of the assignment service class
        :param assignment_repo: the repository for the assignments
        :param assignment_validator: the validator for an assignment
        """
        self._undo_redo_service = undo_redo_service
        self._assignment_repo = assignment_repo
        self._assignment_validator = assignment_validator
        self._grade_service = grade_service

    def add(self, assignment_id, description, deadline):
        """
        Service method to add a new assignment to the list and its id to the list of assignments ids
        :param assignment_id: the id of the assignment
        :param description: the description of the assignment
        :param deadline: the deadline of the assignment
        :return: -
        """
        new_assignment = self.add_without_record(assignment_id, description, deadline)
        self._assignment_validator.validate(new_assignment)
        undo_ = FunctionCall(self.remove_without_record, assignment_id)
        redo_ = FunctionCall(self.add_without_record, new_assignment.assignment_id, new_assignment.description,
                             new_assignment.deadline)
        self._undo_redo_service.record(Operation(undo_, redo_))

    def add_without_record(self, assignment_id, description, deadline):
        assignment = Assignment(assignment_id, description, deadline)
        self._assignment_repo.add(assignment)
        return assignment

    def add_assignment_and_grades(self, assignment_id, description, deadline, list_of_grades):
        new_assignment = Assignment(assignment_id, description, deadline)
        self._assignment_repo.add(new_assignment)
        if list_of_grades is not None:
            for grade in list_of_grades:
                self._grade_service.add_grade_without_record(grade[0], grade[1], grade[2])

    def remove(self, assignment_id):
        """
        Service method to remove an assignment from the list and its id from the list of assignments ids
        :param assignment_id: the id of the assignment we want to remove
        :return: -
        """
        assignment, list_of_grades = self.remove_without_record(assignment_id)
        undo_ = FunctionCall(self.add_assignment_and_grades, assignment.assignment_id, assignment.description,
                             assignment.deadline, list_of_grades)
        redo_ = FunctionCall(self.remove_without_record, assignment.assignment_id)
        self._undo_redo_service.record(Operation(undo_, redo_))

    def remove_without_record(self, assignment_id):
        check_assignment = Assignment(assignment_id, "description", date(2020, 1, 1))
        self._assignment_validator.validate(check_assignment)
        assignment = self._assignment_repo.remove(assignment_id)
        list_of_grades = self._grade_service.remove_by_assignment(assignment_id)
        return assignment, list_of_grades

    def update(self, assignment_id, new_description, new_deadline):
        """
        Service method to update an assignment from the list
        :param assignment_id: the id of the assignment we want to update
        :param new_description: the new description (can be the same)
        :param new_deadline: the new deadline (can be the same)
        :return: -
        """
        old_description, old_deadline = self.update_without_record(assignment_id, new_description, new_deadline)
        undo_ = FunctionCall(self.update_without_record, assignment_id, old_description, old_deadline)
        redo_ = FunctionCall(self.update_without_record, assignment_id, new_description, new_deadline)
        self._undo_redo_service.record(Operation(undo_, redo_))

    def update_without_record(self, assignment_id, new_description, new_deadline):
        old_description, old_deadline = self._assignment_repo.update(assignment_id, new_description, new_deadline)
        return old_description, old_deadline

    def get_assignment_by_id(self, assignment_id):
        return self._assignment_repo.get_assignment_by_id(assignment_id)

    def get_all(self):
        """
        Service function to get all the assignments
        :return: The list of assignments
        """
        return self._assignment_repo.get_all_assignments()

    @staticmethod
    def random_assignment_id(letter_count, digits_count):
        """
        Function to randomly generate an assignment id
        :param letter_count: how many letters the id has
        :param digits_count: how many digits the id has
        :return: the assignment id
        """
        letters = string.ascii_letters
        digits = string.digits
        assignment_id = ''.join(random.choice(letters) for i in range(letter_count))
        assignment_id += ''.join(random.choice(digits) for i in range(digits_count))
        return assignment_id

    def initialise(self):
        description_list = ["Algebra test", "CSA test", "FP test", "Mathematical Analysis test",
                            "Computational Logic test",
                            "Algebra hw", "CSA hw", "FP hw", "Mathematical Analysis hw", "Computational Logic hw",
                            "Chemistry hw", "Biology hw", "History hw", "Literature hw", "English hw",
                            "Chemistry test", "Biology test", "History test", "Literature test", "English test"]
        for index in range(10):
            assignment_id = self.random_assignment_id(3, 4)
            description = random.choice(description_list)
            deadline_year = random.randint(2020, 2021)
            deadline_month = random.randint(1, 12)
            if deadline_month == 2:
                deadline_day = random.randint(1, 28)
            else:
                deadline_day = random.randint(1, 30)
            deadline = date(deadline_year, deadline_month, deadline_day)
            self.add_without_record(assignment_id, description, deadline)


class GradeService:
    """
    Grade service class, comunicates with the repo class.
    """
    def __init__(self, student_repo, assignment_repo, grade_repo, undo_redo_service):
        """
        :param grade_repo: Repository for grades
        """
        self._student_repo = student_repo
        self._assignment_repo = assignment_repo
        self._undo_redo_service = undo_redo_service
        self._grade_repo = grade_repo

    def add(self, student_id, assignment_id, grade):
        """
        Add a new ungraded assignment.
        :param student_id: the id of the student
        :param assignment_id: the id of the assignment
        :param grade: the grade (in this case 0)
        :return: -
        """
        self.add_grade_without_record(student_id, assignment_id, grade)
        undo_ = FunctionCall(self.remove_last_grades, 1)
        redo_ = FunctionCall(self.add_grade_without_record, student_id, assignment_id, grade)
        self._undo_redo_service.record(Operation(undo_, redo_))

    def add_grade_without_record(self, student_id, assignment_id, grade):
        new_grade = Grade(student_id, assignment_id, grade)
        self._grade_repo.add(new_grade)
        return new_grade

    def remove(self, student_id, assignment_id):
        list_of_grades = []
        for grade in self._grade_repo.get_all_grades():
            if grade.student_id == student_id:
                if grade.assignment_id == assignment_id:
                    grade_details = (grade.student_id, grade.assignment_id, grade.grade)
                    list_of_grades.append(grade_details)
                    self._grade_repo.remove(grade.student_id, grade.assignment_id)
        return list_of_grades

    def remove_by_student(self, student_id):
        list_of_grades = []
        for grade in self._grade_repo.get_all_grades():
            if grade.student_id == student_id:
                grade_details = (grade.student_id, grade.assignment_id, grade.grade)
                list_of_grades.append(grade_details)
                self._grade_repo.remove(grade.student_id, grade.assignment_id)
        return list_of_grades

    def remove_by_assignment(self, assignment_id):
        list_of_grades = []
        for grade in self._grade_repo.get_all_grades():
            if grade.assignment_id == assignment_id:
                grade_details = (grade.student_id, grade.assignment_id, grade.grade)
                list_of_grades.append(grade_details)
                self._grade_repo.remove(grade.student_id, grade.assignment_id)
        return list_of_grades

    def remove_last_grades(self, number_of_grades):
        self._grade_repo.remove_last_grades(number_of_grades)

    def is_graded(self, student_id, assignment_id):
        for grade in self._grade_repo.get_all_grades():
            if grade.student_id == student_id:
                if grade.assignment_id == assignment_id:
                    return True
        return False

    def add_grade_to_group(self, assignment_id, group):
        number_of_adds = self.add_to_group_without_record(assignment_id, group)
        undo_ = FunctionCall(self.remove_last_grades, number_of_adds)
        redo_ = FunctionCall(self.add_grade_to_group, assignment_id, group)
        self._undo_redo_service.record(Operation(undo_, redo_))

    def add_to_group_without_record(self, assignment_id, group):
        number_of_adds = 0
        if group < 911 or group > 917:
            raise ValueError("Invalid student group!")
        for student in self._student_repo.get_all_students():
            if student.group == group:
                if not self.is_graded(student.student_id, assignment_id):
                    self.add_grade_without_record(student.student_id, assignment_id, 0)
                    number_of_adds += 1
        return number_of_adds

    def grade(self, student_id, assignment_id, grade):
        """
        Grade an ungraded assignment.
        :param student_id: -
        :param assignment_id: -
        :param grade: -
        :return: -
        """
        self.grade_without_record(student_id, assignment_id, grade)
        undo_ = FunctionCall(self.grade_without_record, student_id, assignment_id, 0)
        redo_ = FunctionCall(self.grade_without_record, student_id, assignment_id, grade)
        self._undo_redo_service.record(Operation(undo_, redo_))

    def grade_without_record(self, student_id, assignment_id, grade):
        if self._grade_repo.search_if_grade_exists(student_id, assignment_id) is False:
            raise RepositoryException("The student and the assignment are not linked!")
        self._grade_repo.grade(student_id, assignment_id, grade)

    def get_all(self):
        """
        :return: A copy of the list of all grades.
        """
        return self._grade_repo.get_all_grades()

    def initialise(self):
        for index in range(15):
            random_student_id = self._student_repo.get_random_id()
            random_assignment_id = self._assignment_repo.get_random_id()
            random_grade = float(random.randint(0, 10))
            random_grading = Grade(random_student_id, random_assignment_id, random_grade)
            if random_grading not in self._grade_repo.get_all_grades():
                self._grade_repo.add(random_grading)
            else:
                index -= 1
