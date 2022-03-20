import unittest
from datetime import date

from src.exceptions import RepositoryException, StudentException, AssignmentException
from src.domain.domain import Student, Assignment, Grade
from src.repository.repo import RepositoryStudents, RepositoryAssignments, RepositoryGrade
from src.services.service import GradeService, StudentService, AssignmentService
from src.services.statistics import Statistics, unique
from src.services.undo_redo_service import UndoRedoService, UndoRedoException
from src.validators.validator import StudentValidator, AssignmentValidator


class TestStudent(unittest.TestCase):
    def test_student(self):
        student1 = Student("43kdss", "Brinza Alina", 911)
        self.assertEqual(student1.student_id, "43kdss")
        self.assertEqual(student1.name, "Brinza Alina")
        self.assertEqual(student1.group, 911)
        self.assertEqual(str(student1), "ID: 43kdss , Name: Brinza Alina, from group 911")

    def test_name_and_group_setter(self):
        student2 = Student("42kdss", "Brinza Alina", 911)
        student2.name = "Alina"
        student2.group = 912
        self.assertEqual(student2.name, "Alina")
        self.assertEqual(student2.group, 912)

    def test_equal(self):
        student3 = Student("123456", "Alina", 911)
        student4 = Student("654321", "Elena", 912)
        self.assertNotEqual(student3, student4)


class TestStudentValidator(unittest.TestCase):
    def test_student_validator_student_id(self):
        student1 = Student("3sew2e", "Brinza Alina", 911)
        StudentValidator.validate(student1)
        try:
            student1 = Student("3sew2", "Brinza Alina", 911)
            StudentValidator.validate(student1)
        except StudentException as se:
            self.assertEqual(str(se), "Student id must be a combination of 6 letters and numbers.")

    def test_student_validator_name(self):
        student1 = Student("3sew2e", "Brinza Alina", 911)
        StudentValidator.validate(student1)

        try:
            student1 = Student("3sew2e", "", 911)
            StudentValidator.validate(student1)
        except StudentException as se:
            self.assertEqual(str(se), "The input for the name is empty.")

        try:
            student1 = Student("3sew2e", "Brinz2 Alina", 911)
            StudentValidator.validate(student1)
        except StudentException as se:
            self.assertEqual(str(se), "Invalid student name!")

    def test_student_validator_group(self):
        student1 = Student("3sew2e", "Brinza Alina", 911)
        StudentValidator.validate(student1)

        try:
            student1 = Student("3sew2e", "Brinza Alina", 0)
            StudentValidator.validate(student1)
        except StudentException as se:
            self.assertEqual(str(se), "Invalid group!")


class TestAssignment(unittest.TestCase):
    def test_assignment(self):
        assignment1 = Assignment("MLE0020", "Algebra", date(2020, 11, 19))
        self.assertEqual(assignment1.assignment_id, "MLE0020")
        self.assertEqual(assignment1.description, "Algebra")
        self.assertEqual(assignment1.deadline, date(2020, 11, 19))
        self.assertEqual(str(assignment1), "Assignment MLE0020 -> description: Algebra with deadline: 2020-11-19")

    def test_description_and_deadline_setter(self):
        assignment2 = Assignment("MLE0002", "Mathematical Analysis", date(2020, 11, 20))
        assignment2.description = "algebra"
        assignment2.deadline = date(2020, 12, 25)
        self.assertEqual(assignment2.description, "algebra")
        self.assertEqual(assignment2.deadline, date(2020, 12, 25))

    def test_equal(self):
        assignment3 = Assignment("MLE5004", "CSA", date(2020, 11, 17))
        assignment4 = Assignment("MLE2004", "CAS", date(2020, 12, 14))
        self.assertNotEqual(assignment4, assignment3)


class TestAssignmentValidator(unittest.TestCase):
    def test_assignment_validator_assignment_id(self):
        assignment1 = Assignment("MLE0020", "Algebra", date(2020, 11, 19))
        AssignmentValidator.validate(assignment1)

        try:
            assignment1 = Assignment("MLE002", "Algebra", date(2020, 11, 19))
            AssignmentValidator.validate(assignment1)
        except AssignmentException as ae:
            self.assertEqual(str(ae), "Assignment id must be a combination of 7 letters and digits.")

        try:
            assignment1 = Assignment("0LE0020", "Algebra", date(2020, 11, 19))
            AssignmentValidator.validate(assignment1)
        except AssignmentException as ae:
            self.assertEqual(str(ae), "The assignment id has a wrong format.")

        try:
            assignment1 = Assignment("M0E0020", "Algebra", date(2020, 11, 19))
            AssignmentValidator.validate(assignment1)
        except AssignmentException as ae:
            self.assertEqual(str(ae), "The assignment id has a wrong format.")

        try:
            assignment1 = Assignment("ML00020", "Algebra", date(2020, 11, 19))
            AssignmentValidator.validate(assignment1)
        except AssignmentException as ae:
            self.assertEqual(str(ae), "The assignment id has a wrong format.")

        try:
            assignment1 = Assignment("MLEE020", "Algebra", date(2020, 11, 19))
            AssignmentValidator.validate(assignment1)
        except AssignmentException as ae:
            self.assertEqual(str(ae), "The assignment id has a wrong format.")

    def test_assignment_validator_date(self):
        assignment1 = Assignment("MLE0020", "Algebra", date(2020, 11, 19))
        AssignmentValidator.validate(assignment1)

        try:
            assignment1 = Assignment("MLE0020", "Algebra", date(0, 0, 0))
            AssignmentValidator.validate(assignment1)
        except ValueError as ve:
            self.assertEqual(str(ve), "year 0 is out of range")


class TestGrade(unittest.TestCase):
    def test_grade(self):
        grade1 = Grade("13fr3e", "MLE0020", 10)
        self.assertEqual(grade1.student_id, "13fr3e")
        self.assertEqual(grade1.assignment_id, "MLE0020")
        self.assertEqual(grade1.grade, 10)
        self.assertEqual(str(grade1), "The grade for student 13fr3e for the assignment MLE0020 is 10.0")
        grade2 = Grade("123456", "MLE0000", 0)
        self.assertEqual(str(grade2), "Assigned to student 123456 the assignment MLE0000")

    def test_grade_setter(self):
        grade3 = Grade("123457", "MLE0000", 0)
        grade3.grade = 10
        self.assertEqual(grade3.grade, 10)

    def test_equal(self):
        grade4 = Grade("102020", "MLE0000", 9)
        grade5 = Grade("100000", "MLE0000", 9)
        self.assertNotEqual(grade5, grade4)


class TestStudentRepository(unittest.TestCase):
    def setUp(self):
        self._student_repository = RepositoryStudents()
        self._student_repository.add(Student('123456', 'Mike', 913))
        self._student_repository.add(Student('123546', 'Lucas', 917))
        self._student_repository.add(Student('123645', 'Anna', 915))
        self._student_repository.add(Student('123765', 'Mary', 911))
        self._student_list = self._student_repository.get_all_students()

    def test_repository_store(self):
        self.assertEqual(len(self._student_repository), 4)
        self.assertRaises(RepositoryException, self._student_repository.add, Student('123456', 'John', 913))

    def test_repository_remove(self):
        self._student_repository.remove('123456')
        self.assertEqual(len(self._student_repository), 3)
        self._student_repository.remove('123546')
        self._student_repository.remove('123645')
        self._student_repository.remove('123765')
        self.assertEqual(len(self._student_repository), 0)
        try:
            self._student_repository.remove('999999')
        except RepositoryException as re:
            self.assertEqual(str(re), "The list of students is already empty!")
        self.assertRaises(RepositoryException, self._student_repository.remove, '999999')
        self._student_repository.add(Student('123765', 'Mary', 911))
        self.assertRaises(RepositoryException, self._student_repository.remove, '999999')

    def test_search_student(self):
        self.assertTrue(self._student_repository.search_student_id('123546'))
        self.assertFalse(self._student_repository.search_student_id('123199'))

    def test_update_student(self):
        self._student_repository.update('123456', 'Miguel', 912)
        self.assertEqual(self._student_list[0].name, 'Miguel')
        self.assertEqual(self._student_list[0].group, 912)
        self.assertRaises(RepositoryException, self._student_repository.update, '123956', 'Miguel', 912)

    def test_get_student_by_id(self):
        self.assertIsNone(self._student_repository.get_student_by_id('789500'))
        self.assertEqual(self._student_repository.get_student_by_id('123456'), self._student_list[0])

    def test_get_random_id(self):
        student_id = int(self._student_repository.get_random_id())
        self.assertGreaterEqual(student_id, 123456)
        self.assertLessEqual(student_id, 123780)


class TestAssignmentRepository(unittest.TestCase):
    def setUp(self):
        self._assignment_repository = RepositoryAssignments()
        self._assignment_repository.add(Assignment('MLE0001', 'First description', date(2022, 3, 17)))
        self._assignment_repository.add(Assignment('MLE0002', 'Second description', date(2022, 4, 16)))
        self._assignment_repository.add(Assignment('MLE0003', 'Third description', date(2022, 6, 15)))
        self._assignment_repository.add(Assignment('MLE0004', 'Fourth description', date(2021, 8, 14)))
        self._assignment_list = self._assignment_repository.get_all_assignments()

    def test_repository_store(self):
        self.assertEqual(len(self._assignment_repository), 4)
        self.assertRaises(RepositoryException, self._assignment_repository.add, Assignment('MLE0001', 'Test Description', date.today()))

    def test_repository_remove(self):
        self._assignment_repository.remove('MLE0001')
        self.assertEqual(len(self._assignment_repository), 3)
        self.assertRaises(RepositoryException, self._assignment_repository.remove, 'MLE0000')
        self._assignment_repository.remove('MLE0002')
        self._assignment_repository.remove('MLE0003')
        self._assignment_repository.remove('MLE0004')
        self.assertEqual(len(self._assignment_repository), 0)
        self.assertRaises(RepositoryException, self._assignment_repository.remove, 'MLE9999')

    def test_update_assignment(self):
        self._assignment_repository.update('MLE0001', 'algebra', date(2021, 1, 1))
        self.assertEqual(self._assignment_repository.get_assignment_description('MLE0001'), 'algebra')
        self.assertEqual(self._assignment_repository.get_assignment_deadline('MLE0001'), date(2021, 1, 1))
        self.assertRaises(RepositoryException, self._assignment_repository.update, 'MLE9999', 'algebra', date.today())

    def test_search_assignment(self):
        self.assertTrue(self._assignment_repository.search_assignment_id('MLE0001'))
        self.assertFalse(self._assignment_repository.search_assignment_id('MLE9999'))

    def test_get_assignment_by_id(self):
        self.assertIsNone(self._assignment_repository.get_assignment_by_id('MLE9999'))
        self.assertEqual(self._assignment_repository.get_assignment_by_id('MLE0001'), self._assignment_list[0])

    def test_get_random_id(self):
        assignment_id = self._assignment_repository.get_random_id()
        self.assertEqual(len(assignment_id), 7)
        assignment_id = int(assignment_id[6:])
        self.assertGreaterEqual(assignment_id, 1)
        self.assertLessEqual(assignment_id, 4)


class TestGradesRepository(unittest.TestCase):
    def setUp(self):
        self._grades_repository = RepositoryGrade()
        self._grades_repository.add(Grade('000001', 'MLE0001', 0))
        self._grades_repository.add(Grade('000002', 'MLE0002', 10))
        self._grades_repository.add(Grade('000003', 'MLE0003', 0))
        self._grades_repository.add(Grade('000004', 'MLE0004', 0))
        self._grades_repository.add(Grade('000005', 'MLE0005', 0))
        self._grades_list = self._grades_repository.get_all_grades()

    def test_repository_store(self):
        self.assertEqual(len(self._grades_repository), 5)
        self.assertRaises(RepositoryException, self._grades_repository.add, Grade('000001', 'MLE0001', 10))

    def test_repository_remove(self):
        self._grades_repository.remove('000001', 'MLE0001')
        self.assertEqual(len(self._grades_repository), 4)
        self.assertRaises(RepositoryException, self._grades_repository.remove, '999999', 'MLE9999')

    def test_repository_remove_by(self):
        self._grades_repository.remove_by_assignment('MLE0001')
        self.assertEqual(len(self._grades_repository), 4)
        self._grades_repository.remove_by_student('000002')
        self.assertEqual(len(self._grades_repository), 3)

    def test_searches(self):
        self.assertTrue(self._grades_repository.search_student_id('000001'))
        self.assertFalse(self._grades_repository.search_student_id('999999'))
        self.assertTrue(self._grades_repository.search_assignment_id('MLE0001'))
        self.assertFalse(self._grades_repository.search_assignment_id('MLE9999'))
        self.assertTrue(self._grades_repository.search_if_grade_exists('000001', 'MLE0001'))
        self.assertFalse(self._grades_repository.search_if_grade_exists('000001', 'MLE9999'))

    def test_remove_last_grades(self):
        self._grades_repository.remove_last_grades(2)
        self.assertEqual(len(self._grades_repository), 3)

    def test_update_grade(self):
        self._grades_repository.grade('000001', 'MLE0001', 10)
        self.assertEqual(self._grades_list[0].grade, 10)
        self.assertRaises(RepositoryException, self._grades_repository.grade, '000002', 'MLE0002', 10)
        self._grades_repository.grade('000003', 'MLE0003', 0)
        self._grades_list = self._grades_repository.get_all_grades()
        self.assertEqual(self._grades_list[2].grade, 0)
        self.assertRaises(ValueError, self._grades_repository.grade, '000004', 'MLE0004', -1)
        self.assertRaises(ValueError, self._grades_repository.grade, '000004', 'MLE0004', 11)


class TestAllService(unittest.TestCase):
    def setUp(self):
        student_repository = RepositoryStudents()
        student_validator = StudentValidator()
        assignment_repository = RepositoryAssignments()
        assignment_validator = AssignmentValidator()
        grades_repository = RepositoryGrade()
        self._undo_redo_service = UndoRedoService()
        self._grade_service = GradeService(student_repository, assignment_repository, grades_repository, self._undo_redo_service)
        self._student_service = StudentService(student_repository, student_validator, self._undo_redo_service, self._grade_service)
        self._assignment_service = AssignmentService(assignment_repository, assignment_validator, self._undo_redo_service, self._grade_service)

    def test_initialises(self):
        self._student_service.initialise()
        list_of_students = self._student_service.get_all()
        self.assertLessEqual(len(list_of_students), 10)

        self._assignment_service.initialise()
        list_of_assignments = self._assignment_service.get_all()
        self.assertLessEqual(len(list_of_assignments), 10)

        self._grade_service.initialise()
        list_of_grades = self._grade_service.get_all()
        self.assertLessEqual(len(list_of_grades), 15)

    def test_student_add(self):
        self._student_service.add('000001', 'Michael', 911)
        self.assertEqual(self._student_service.add_without_record('000002', 'test', 911), Student('000002', 'test', 911))
        list_of_students = self._student_service.get_all()
        self.assertEqual(len(list_of_students), 2)
        self._undo_redo_service.undo()
        list_of_students = self._student_service.get_all()
        self.assertEqual(len(list_of_students), 1)
        self.assertRaises(UndoRedoException, self._undo_redo_service.undo)
        self._undo_redo_service.redo()
        list_of_students = self._student_service.get_all()
        self.assertEqual(len(list_of_students), 2)
        self.assertRaises(UndoRedoException, self._undo_redo_service.redo)

    def test_student_remove(self):
        self._student_service.add('000001', 'Michael', 911)
        self._student_service.remove('000001')
        list_of_students = self._student_service.get_all()
        self.assertEqual(len(list_of_students), 0)
        self._undo_redo_service.undo()
        list_of_students = self._student_service.get_all()
        self.assertEqual(len(list_of_students), 1)
        self._undo_redo_service.undo()
        self.assertRaises(UndoRedoException, self._undo_redo_service.undo)
        self._undo_redo_service.redo()
        list_of_students = self._student_service.get_all()
        self.assertEqual(len(list_of_students), 1)
        self._undo_redo_service.redo()
        self.assertRaises(UndoRedoException, self._undo_redo_service.redo)

    def test_student_update(self):
        self._student_service.add('000001', 'Michael', 911)
        self._student_service.add('000002', 'John', 912)
        self._student_service.add('000003', 'Mary', 913)
        self._student_service.update('000001', 'Alex', 914)
        list_of_students = self._student_service.get_all()
        first_student = list_of_students[0]
        self.assertEqual(first_student.name, 'Alex')
        self.assertEqual(first_student.group, 914)

    def test_assignment_add(self):
        self._assignment_service.add('MLE0001', 'description one', date(2022, 1, 1))
        self.assertEqual(self._assignment_service.add_without_record('MLE0002', 'description two', date(2020, 1, 1)), Assignment('MLE0002', 'description two', date(2020, 1, 1)))
        list_of_assignments = self._assignment_service.get_all()
        self.assertEqual(len(list_of_assignments), 2)
        self._undo_redo_service.undo()
        list_of_assignments = self._assignment_service.get_all()
        self.assertEqual(len(list_of_assignments), 1)
        self.assertRaises(UndoRedoException, self._undo_redo_service.undo)
        self._undo_redo_service.redo()
        list_of_assignments = self._assignment_service.get_all()
        self.assertEqual(len(list_of_assignments), 2)
        self.assertRaises(UndoRedoException, self._undo_redo_service.redo)

    def test_assignment_remove(self):
        self._assignment_service.add('MLE0001', 'description one', date(2022, 1, 1))
        self._assignment_service.add('MLE0002', 'description two', date(2022, 2, 2))
        self._assignment_service.add('MLE0003', 'description three', date(2022, 3, 3))
        self._assignment_service.remove('MLE0001')
        list_of_assignments = self._assignment_service.get_all()
        self.assertEqual(len(list_of_assignments), 2)

    def test_assignment_update(self):
        self._assignment_service.add('MLE0001', 'description one', date(2022, 1, 1))
        self._assignment_service.add('MLE0002', 'description two', date(2022, 2, 2))
        self._assignment_service.add('MLE0003', 'description three', date(2022, 3, 3))
        self._assignment_service.update('MLE0001','algebra', date(2021, 4, 4))
        list_of_assignments = self._assignment_service.get_all()
        first_assignment = list_of_assignments[0]
        self.assertEqual(first_assignment.description, 'algebra')
        self.assertEqual(first_assignment.deadline, date(2021, 4, 4))

    def test_get_assignment_by_id(self):
        self._assignment_service.add('MLE0001', 'description one', date(2022, 1, 1))
        assignment = self._assignment_service.get_assignment_by_id('MLE0001')
        self.assertEqual(assignment, Assignment('MLE0001', 'description one', date(2022, 1, 1)))

    def test_grades_add(self):
        self._student_service.add('000001', 'Michael', 911)
        self._student_service.add('000002', 'John', 912)
        self._student_service.add('000003', 'Mary', 913)
        self._assignment_service.add('MLE0001', 'description one', date(2022, 1, 1))
        self._assignment_service.add('MLE0002', 'description two', date(2022, 2, 2))
        self._assignment_service.add('MLE0003', 'description three', date(2022, 3, 3))
        self._grade_service.add('000001', 'MLE0001', 7)
        list_of_grades = self._grade_service.get_all()
        self.assertEqual(len(list_of_grades), 1)
        self._undo_redo_service.undo()
        list_of_grades = self._grade_service.get_all()
        self.assertEqual(len(list_of_grades), 0)
        self._undo_redo_service.redo()
        list_of_grades = self._grade_service.get_all()
        self.assertEqual(len(list_of_grades), 1)
        self.assertRaises(UndoRedoException, self._undo_redo_service.redo)

    def test_grade_remove(self):
        self._student_service.add('000001', 'Michael', 911)
        self._student_service.add('000002', 'John', 912)
        self._student_service.add('000003', 'Mary', 913)
        self._assignment_service.add('MLE0001', 'description one', date(2022, 1, 1))
        self._assignment_service.add('MLE0002', 'description two', date(2022, 2, 2))
        self._assignment_service.add('MLE0003', 'description three', date(2022, 3, 3))
        self._grade_service.add('000001', 'MLE0001', 7)
        list_of_grades = self._grade_service.remove('000001', 'MLE0001')

    def test_grade_remove_by_student(self):
        self._student_service.add('000001', 'Michael', 911)
        self._student_service.add('000002', 'John', 912)
        self._student_service.add('000003', 'Mary', 913)
        self._assignment_service.add('MLE0001', 'description one', date(2022, 1, 1))
        self._assignment_service.add('MLE0002', 'description two', date(2022, 2, 2))
        self._assignment_service.add('MLE0003', 'description three', date(2022, 3, 3))
        self._grade_service.add('000001', 'MLE0001', 7)
        list_of_grades = self._grade_service.remove_by_student('000001')
        self.assertEqual(len(list_of_grades), 1)

    def test_grade_remove_by_assignment(self):
        self._student_service.add('000001', 'Michael', 911)
        self._student_service.add('000002', 'John', 912)
        self._student_service.add('000003', 'Mary', 913)
        self._assignment_service.add('MLE0001', 'description one', date(2022, 1, 1))
        self._assignment_service.add('MLE0002', 'description two', date(2022, 2, 2))
        self._assignment_service.add('MLE0003', 'description three', date(2022, 3, 3))
        self._grade_service.add('000001', 'MLE0001', 7)
        list_of_grades = self._grade_service.remove_by_assignment('MLE0001')
        self.assertEqual(len(list_of_grades), 1)

    def test_if_graded(self):
        self._student_service.add('000001', 'Michael', 911)
        self._student_service.add('000002', 'John', 912)
        self._student_service.add('000003', 'Mary', 913)
        self._assignment_service.add('MLE0001', 'description one', date(2022, 1, 1))
        self._assignment_service.add('MLE0002', 'description two', date(2022, 2, 2))
        self._assignment_service.add('MLE0003', 'description three', date(2022, 3, 3))
        self._grade_service.add('000001', 'MLE0001', 7)
        self.assertTrue(self._grade_service.is_graded('000001', 'MLE0001'))
        self.assertFalse(self._grade_service.is_graded('000001', 'MLE0002'))

    def test_grading(self):
        self._student_service.add('000001', 'Michael', 911)
        self._student_service.add('000002', 'John', 912)
        self._student_service.add('000003', 'Mary', 913)
        self._assignment_service.add('MLE0001', 'description one', date(2022, 1, 1))
        self._assignment_service.add('MLE0002', 'description two', date(2022, 2, 2))
        self._assignment_service.add('MLE0003', 'description three', date(2022, 3, 3))
        self._grade_service.add_grade_without_record('000001', 'MLE0001', 0)
        list_of_grades = self._grade_service.get_all()
        self.assertEqual(list_of_grades[0].grade, 0)
        self._grade_service.grade('000001', 'MLE0001', 9)
        list_of_grades = self._grade_service.get_all()
        self.assertEqual(list_of_grades[0].grade, 9)
        self._undo_redo_service.undo()
        list_of_grades = self._grade_service.get_all()
        self.assertEqual(list_of_grades[0].grade, 0)
        self.assertRaises(RepositoryException, self._grade_service.grade_without_record, '000001', 'MLE0002', 10)

    def test_add_grade_to_group(self):
        self._student_service.add('000001', 'Michael', 911)
        self._student_service.add('000002', 'John', 912)
        self._student_service.add('000003', 'Mary', 913)
        self._assignment_service.add('MLE0001', 'description one', date(2022, 1, 1))
        self._assignment_service.add('MLE0002', 'description two', date(2022, 2, 2))
        self._assignment_service.add('MLE0003', 'description three', date(2022, 3, 3))
        self._grade_service.add_grade_to_group('MLE0001', 911)
        grades_list = self._grade_service.get_all()
        self.assertEqual(len(grades_list), 1)
        self.assertRaises(ValueError, self._grade_service.add_to_group_without_record, 'MLE0001', 930)

    def test_cascading_undo_students(self):
        self._student_service.add_without_record('000001', 'Michael', 911)
        self._student_service.add_without_record('000002', 'John', 912)
        self._student_service.add_without_record('000003', 'Mary', 911)
        self._assignment_service.add_without_record('MLE0001', 'description one', date(2022, 1, 1))
        self._assignment_service.add_without_record('MLE0002', 'description two', date(2022, 2, 2))
        self._assignment_service.add_without_record('MLE0003', 'description three', date(2019, 3, 3))
        self._grade_service.add_grade_without_record('000001', 'MLE0002', 7)
        self._grade_service.add_grade_without_record('000001', 'MLE0001', 8)
        list_of_grades = self._grade_service.get_all()
        self.assertEqual(len(list_of_grades), 2)
        self._student_service.remove('000001')
        list_of_grades = self._grade_service.get_all()
        self.assertEqual(len(list_of_grades), 0)
        self._undo_redo_service.undo()
        list_of_grades = self._grade_service.get_all()
        self.assertEqual(len(list_of_grades), 2)

    def test_cascading_undo_assignments(self):
        self._student_service.add_without_record('000001', 'Michael', 911)
        self._student_service.add_without_record('000002', 'John', 912)
        self._student_service.add_without_record('000003', 'Mary', 911)
        self._assignment_service.add_without_record('MLE0001', 'description one', date(2022, 1, 1))
        self._assignment_service.add_without_record('MLE0002', 'description two', date(2022, 2, 2))
        self._assignment_service.add_without_record('MLE0003', 'description three', date(2019, 3, 3))
        self._grade_service.add_grade_without_record('000001', 'MLE0001', 7)
        self._grade_service.add_grade_without_record('000002', 'MLE0001', 8)
        list_of_grades = self._grade_service.get_all()
        self.assertEqual(len(list_of_grades), 2)
        self._assignment_service.remove('MLE0001')
        list_of_grades = self._grade_service.get_all()
        self.assertEqual(len(list_of_grades), 0)
        self._undo_redo_service.undo()
        list_of_grades = self._grade_service.get_all()
        self.assertEqual(len(list_of_grades), 2)


class TestStatistics(unittest.TestCase):
    def test_unique_list(self):
        list = [1, 1, 2, 2, 3, 3]
        unique_list = unique(list)
        self.assertEqual(len(unique_list), 3)
        self.assertEqual(unique_list, [1, 2, 3])

    def test_class(self):
        student_validator = StudentValidator
        assignment_validator = AssignmentValidator
        student_repo = RepositoryStudents()
        assignment_repo = RepositoryAssignments()
        grade_repo = RepositoryGrade()
        undo_redo_service = UndoRedoService()
        grade_service = GradeService(student_repo, assignment_repo, grade_repo, undo_redo_service)
        student_service = StudentService(student_repo, student_validator, undo_redo_service, grade_service)
        assignment_service = AssignmentService(assignment_repo, assignment_validator, undo_redo_service, grade_service)
        statistics = Statistics(grade_service, assignment_service, student_service)
        self.assertEqual(statistics.grade_service, grade_service)
        self.assertEqual(statistics.assignment_service, assignment_service)
        self.assertEqual(statistics.student_service, student_service)
        elem = [1, 2]
        second = statistics.take_second(elem)
        self.assertEqual(second, 2)

    def test_unique_assignments(self):
        student_validator = StudentValidator
        assignment_validator = AssignmentValidator
        student_repo = RepositoryStudents()
        assignment_repo = RepositoryAssignments()
        grade_repo = RepositoryGrade()
        undo_redo_service = UndoRedoService()
        grade_service = GradeService(student_repo, assignment_repo, grade_repo, undo_redo_service)
        student_service = StudentService(student_repo, student_validator, undo_redo_service, grade_service)
        assignment_service = AssignmentService(assignment_repo, assignment_validator, undo_redo_service, grade_service)
        statistics = Statistics(grade_service, assignment_service, student_service)
        student1 = Student("000001", "Alina", 911)
        student2 = Student("000002", "Elena", 912)
        student_repo.add(student1)
        student_repo.add(student2)
        assignment = Assignment("MLE0000", "test", date(2020, 12, 12))
        assignment_repo.add(assignment)
        grade1 = Grade("000001", "MLE0000", 10)
        grade2 = Grade("000002", "MLE0000", 9)
        grade_repo.add(grade1)
        grade_repo.add(grade2)
        unique_assignments = statistics.get_unique_assignments()
        self.assertEqual(len(unique_assignments), 1)

    def test_statistics_1(self):
        student_validator = StudentValidator
        assignment_validator = AssignmentValidator
        student_repo = RepositoryStudents()
        assignment_repo = RepositoryAssignments()
        grade_repo = RepositoryGrade()
        undo_redo_service = UndoRedoService()
        grade_service = GradeService(student_repo, assignment_repo, grade_repo, undo_redo_service)
        student_service = StudentService(student_repo, student_validator, undo_redo_service, grade_service)
        assignment_service = AssignmentService(assignment_repo, assignment_validator, undo_redo_service, grade_service)
        statistics = Statistics(grade_service, assignment_service, student_service)
        student1 = Student("000001", "Alina", 911)
        student2 = Student("000002", "Elena", 912)
        student_repo.add(student1)
        student_repo.add(student2)
        assignment = Assignment("MLE0000", "test", date(2020, 12, 12))
        assignment_repo.add(assignment)
        grade1 = Grade("000001", "MLE0000", 10)
        grade2 = Grade("000002", "MLE0000", 9)
        grade_repo.add(grade1)
        grade_repo.add(grade2)
        unique_students = statistics.statistics_1("MLE0000")
        self.assertEqual(len(unique_students), 2)

    def test_statistics_2(self):
        student_validator = StudentValidator
        assignment_validator = AssignmentValidator
        student_repo = RepositoryStudents()
        assignment_repo = RepositoryAssignments()
        grade_repo = RepositoryGrade()
        undo_redo_service = UndoRedoService()
        grade_service = GradeService(student_repo, assignment_repo, grade_repo, undo_redo_service)
        student_service = StudentService(student_repo, student_validator, undo_redo_service, grade_service)
        assignment_service = AssignmentService(assignment_repo, assignment_validator, undo_redo_service, grade_service)
        statistics = Statistics(grade_service, assignment_service, student_service)
        student1 = Student("000001", "Alina", 911)
        student2 = Student("000002", "Elena", 912)
        student_repo.add(student1)
        student_repo.add(student2)
        assignment = Assignment("MLE0000", "test", date(2020, 12, 1))
        assignment_repo.add(assignment)
        grade1 = Grade("000001", "MLE0000", 0)
        grade2 = Grade("000002", "MLE0000", 0)
        grade_repo.add(grade1)
        grade_repo.add(grade2)
        unique_late_students = statistics.statistics_2()
        self.assertEqual(len(unique_late_students), 2)

    def test_statistics_3(self):
        student_validator = StudentValidator
        assignment_validator = AssignmentValidator
        student_repo = RepositoryStudents()
        assignment_repo = RepositoryAssignments()
        grade_repo = RepositoryGrade()
        undo_redo_service = UndoRedoService()
        grade_service = GradeService(student_repo, assignment_repo, grade_repo, undo_redo_service)
        student_service = StudentService(student_repo, student_validator, undo_redo_service, grade_service)
        assignment_service = AssignmentService(assignment_repo, assignment_validator, undo_redo_service, grade_service)
        statistics = Statistics(grade_service, assignment_service, student_service)
        student1 = Student("000001", "Alina", 911)
        student2 = Student("000002", "Elena", 912)
        student_repo.add(student1)
        student_repo.add(student2)
        assignment = Assignment("MLE0000", "test", date(2020, 12, 1))
        assignment_repo.add(assignment)
        grade1 = Grade("000001", "MLE0000", 10)
        grade2 = Grade("000002", "MLE0000", 0)
        grade_repo.add(grade1)
        grade_repo.add(grade2)
        unique_best_students = statistics.statistics_3()
        self.assertEqual(len(unique_best_students), 2)