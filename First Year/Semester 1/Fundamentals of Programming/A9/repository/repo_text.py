from src.domain.domain import Student, Assignment, Grade
from src.repository.repo import RepositoryStudents, RepositoryAssignments, RepositoryGrade


class StudentRepositoryTextFile(RepositoryStudents):
    def __init__(self, file_name):
        self.__file_name = file_name
        super().__init__()
        self.clean_memory()
        self.__append_all_to_file()
        self.__read_all_from_file()

    def __read_all_from_file(self):
        self._list_of_students = self.clean_memory()
        with open(self.__file_name, "r") as f:
            lines = f.readlines()
            f.close()
            for line in lines:
                line = line.strip()
                if line != '':
                    line = line.split(';')
                    student = Student(line[0], line[1], int(line[2]))
                    self._list_of_students.append(student)

    def __append_all_to_file(self):
        with open(self.__file_name, "a") as f:
            for person in self._list_of_students:
                f.write(person.student_id + ';' + person.name + ';' + str(person.group) + '\n')
            f.close()

    def __write_all_to_file(self):
        with open(self.__file_name, "w") as f:
            for person in self._list_of_students:
                f.write(person.student_id + ';' + person.name + ';' + str(person.group) + '\n')
            f.close()

    def __len__(self):
        return super().__len__()

    def add(self, student):
        self.__read_all_from_file()
        student = super().add(student)
        self.__write_all_to_file()
        return student

    def remove(self, student_id):
        self.__read_all_from_file()
        student = super().remove(student_id)
        self.__write_all_to_file()
        return student

    def update(self, student_id, new_name, new_group):
        self.__read_all_from_file()
        old_student_name, old_group = super().update(student_id, new_name, new_group)
        self.__write_all_to_file()
        return old_student_name, old_group

    def search_student_id(self, student_id):
        value = super().search_student_id(student_id)
        return value

    def get_student_by_id(self, student_id):
        value = super().get_student_by_id(student_id)
        return value

    def get_random_id(self):
        return super().get_random_id()

    def get_all_students(self):
        return super().get_all_students()


class AssignmentRepositoryTextFile(RepositoryAssignments):
    def __init__(self, file_name):
        self.__file_name = file_name
        super().__init__()
        self.__append_all_to_file()
        self.__read_all_from_file()

    def __read_all_from_file(self):
        self.clean_memory()
        with open(self.__file_name, "r") as f:
            lines = f.readlines()
            f.close()
            for line in lines:
                if line != '':
                    line = line.split(';')
                    assignment = Assignment(line[0], line[1], line[2])
                    self._list_of_assignments.append(assignment)

    def __append_all_to_file(self):
        with open(self.__file_name, "a") as f:
            for assignment in self._list_of_assignments:
                f.write(assignment.assignment_id + ';' + assignment.description + ';' + str(assignment.deadline) + '\n')
            f.close()

    def __write_all_to_file(self):
        with open(self.__file_name, "w") as f:
            for assignment in self._list_of_assignments:
                f.write(assignment.assignment_id + ';' + assignment.description + ';' + str(assignment.deadline) + '\n')
            f.close()

    def __len__(self):
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


class GradesRepositoryTextFile(RepositoryGrade):
    def __init__(self, file_name):
        self.__file_name = file_name
        super().__init__()
        self.__append_all_to_file()
        self.__read_all_from_file()

    def __read_all_from_file(self):
        f = open(self.__file_name, 'rt')
        lines = f.readlines()
        f.close()
        for line in lines:
            line.strip()
            if line != '':
                line = line.split(';')
                grade = Grade(line[0], line[1], float(line[2].strip(' \n')))
                self._grade_list.append(grade)

    def __append_all_to_file(self):
        f = open(self.__file_name, 'a')
        for grade in self._grade_list:
            f.write(grade.student_id + ';' + grade.assignment_id + ';' + str(float(grade.grade)) + ' \n')
        f.close()


    def __write_all_to_file(self):
        f = open(self.__file_name, 'w')
        for grade in self._grade_list:
            f.write(grade.student_id + ';' + grade.assignment_id + ';' + str(float(grade.grade)) + ' \n')
        f.close()

    def __len__(self):
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
