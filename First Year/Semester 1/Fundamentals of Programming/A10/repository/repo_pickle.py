import pickle

from src.repository.repo import RepositoryStudents, RepositoryAssignments, RepositoryGrade


class StudentRepositoryPickle(RepositoryStudents):
    def __init__(self, file_name):
        self.__file_name = file_name
        super().__init__()
        self.__append_all_to_file()
        self.__read_all_from_file()

    def __read_all_from_file(self):
        with open(self.__file_name, 'rb') as f:
            self._list_of_students = pickle.load(f)
            f.close()

    def __append_all_to_file(self):
        with open(self.__file_name, 'ab') as f:
            pickle.dump(super().get_all_students(), f)
            f.close()

    def __write_all_to_file(self):
        with open(self.__file_name, 'wb') as f:
            pickle.dump(super().get_all_students(), f)
            f.close()

    def __len__(self):
        self.__read_all_from_file()
        return super().__len__()

    def add(self, new_student):
        student = super().add(new_student)
        self.__write_all_to_file()
        return student

    def remove(self, student_id):
        student = super().remove(student_id)
        self.__write_all_to_file()
        return student

    def update(self, student_id, new_name, new_group):
        old_student_name, old_group = super().update(student_id, new_name, new_group)
        self.__write_all_to_file()
        return old_student_name, old_group

    def search_student_id(self, student_id):
        return super().search_student_id(student_id)

    def get_student_by_id(self, student_id):
        return super().get_student_by_id(student_id)

    def get_random_id(self):
        return super().get_random_id()

    def get_all_students(self):
        return super().get_all_students()


class AssignmentRepositoryPickle(RepositoryAssignments):
    def __init__(self, file_name):
        self.__file_name = file_name
        super().__init__()
        self.__append_all_to_file()
        self.__read_all_from_file()

    def __read_all_from_file(self):
        with open(self.__file_name, 'rb') as f:
            self._list_of_assignments = pickle.load(f)
            f.close()

    def __append_all_to_file(self):
        with open(self.__file_name, 'ab') as f:
            pickle.dump(super().get_all_assignments(), f)
            f.close()

    def __write_all_to_file(self):
        with open(self.__file_name, 'wb') as f:
            pickle.dump(super().get_all_assignments(), f)
            f.close()

    def __len__(self):
        self.__read_all_from_file()
        return super().__len__()

    def add(self, new_assignment):
        assignment = super().add(new_assignment)
        self.__write_all_to_file()
        return assignment

    def remove(self, assignment_id):
        searched_assignment = super().remove(assignment_id)
        self.__write_all_to_file()
        return searched_assignment

    def update(self, assignment_id, new_description, new_deadline):
        old_description, old_deadline = super().update(assignment_id, new_description, new_deadline)
        self.__write_all_to_file()
        return old_description, old_deadline

    def search_assignment_id(self, assignment_id):
        return super().search_assignment_id(assignment_id)

    def get_assignment_by_id(self, assignment_id):
        return super().get_assignment_by_id(assignment_id)

    def get_assignment_description(self, assignment_id):
        return super().get_assignment_description(assignment_id)

    def get_assignment_deadline(self, assignment_id):
        return super().get_assignment_deadline(assignment_id)

    def get_random_id(self):
        return super().get_random_id()

    def get_all_assignments(self):
        return super().get_all_assignments()


class GradeRepositoryPickle(RepositoryGrade):
    def __init__(self, file_name):
        self.__file_name = file_name
        super().__init__()
        self.__append_all_to_file()
        self.__read_all_from_file()

    def __read_all_from_file(self):
        with open(self.__file_name, 'rb') as f:
            self._grade_list = pickle.load(f)
            f.close()

    def __append_all_to_file(self):
        with open(self.__file_name, 'ab') as f:
            pickle.dump(super().get_all_grades(), f)
            f.close()

    def __write_all_to_file(self):
        with open(self.__file_name, 'wb') as f:
            pickle.dump(super().get_all_grades(), f)
            f.close()

    def __len__(self):
        self.__read_all_from_file()
        return super().__len__()

    def add(self, new_grade):
        super().add(new_grade)
        self.__write_all_to_file()

    def remove(self, student_id, assignment_id):
        grade = super().remove(student_id, assignment_id)
        self.__write_all_to_file()
        return grade

    def remove_by_student(self, student_id):
        super().remove_by_student(student_id)
        self.__write_all_to_file()

    def remove_by_assignment(self, assignment_id):
        super().remove_by_assignment(assignment_id)
        self.__write_all_to_file()

    def search_student_id(self, student_id):
        return super().search_student_id(student_id)

    def search_assignment_id(self, assignment_id):
        return super().search_assignment_id(assignment_id)

    def search_if_grade_exists(self, student_id, assignment_id):
        return super().search_if_grade_exists(student_id, assignment_id)

    def remove_last_grades(self, number_of_grades):
        super().remove_last_grades(number_of_grades)
        self.__write_all_to_file()

    def grade(self, student_id, assignment_id, grade):
        super().grade(student_id, assignment_id, grade)
        self.__write_all_to_file()

    def get_all_grades(self):
        return super().get_all_grades()