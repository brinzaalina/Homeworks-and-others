"""
This is the validator module, with 2 validators: one for the student, one for the assignment
Validation for the grade is done in the ui and in the domain module class
"""
from src.exceptions import StudentException, AssignmentException


class StudentValidator:
    """
    Class for validating the student class
    """

    @staticmethod
    def validate(student):
        """
        Validates the student to have a valid id, valid name and valid group.
        :return: -
        """
        if len(str(student.student_id)) != 6:
            raise StudentException("Student id must be a combination of 6 letters and numbers.")
        if len(str(student.name)) == 0:
            raise StudentException("The input for the name is empty.")
        if not student.name.replace(" ", "").isalpha():
            raise StudentException("Invalid student name!")
        if int(student.group) < 911 or int(student.group) > 917:
            raise StudentException("Invalid group!")


class AssignmentValidator:
    """
    Class to validate the Assignment class
    """
    @staticmethod
    def validate(assignment):
        """
        Validates the assignment to have a valid id and a valid deadline
        :return: -
        """
        if len(assignment.assignment_id) != 7:
            raise AssignmentException("Assignment id must be a combination of 7 letters and digits.")
        if len(assignment.assignment_id) == 7:
            index = 0
            while index < 7:
                if index == 0:
                    if not assignment.assignment_id[index].isalpha():
                        raise AssignmentException("The assignment id has a wrong format.")
                elif index == 1:
                    if not assignment.assignment_id[index].isalpha():
                        raise AssignmentException("The assignment id has a wrong format.")
                elif index == 2:
                    if not assignment.assignment_id[index].isalpha():
                        raise AssignmentException("The assignment id has a wrong format.")
                else:
                    if not assignment.assignment_id[index].isdigit():
                        raise AssignmentException("The assignment id has a wrong format.")
                index += 1
