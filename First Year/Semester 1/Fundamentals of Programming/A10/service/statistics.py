"""
Statistics module
Implemented this because I didn't want to have a crowded service or ui
"""
from datetime import date

from src.iterable.iterable_structure import IterableStructure


def unique(list_):
    list_set = set(list_)
    unique_list = (list(list_set))
    return unique_list


class Statistics:
    def __init__(self, grade_service, assignment_service, student_service):
        self.grade_service = grade_service
        self.assignment_service = assignment_service
        self.student_service = student_service

    @staticmethod
    def compare_elements(elem1, elem2):
        if float(elem1[1]) >= float(elem2[1]):
            return True
        else:
            return False

    def get_unique_assignments(self):
        grades = self.grade_service.get_all()
        assignments = []
        for index in range(len(grades)):
            assignments.append(grades[index].assignment_id)
        unique_assignments = unique(assignments)
        return unique_assignments

    """
    STATISTICS 1
    """
    def statistics_1(self, assignment_id):
        grades = self.grade_service.get_all()
        students = []
        for index2 in range(len(grades)):
            if grades[index2].assignment_id == assignment_id:
                students.append((grades[index2].student_id, int(grades[index2].grade)))
        students = unique(students)
        unique_students = []
        for i in range(len(students)):
            unique_students.append(students[i])
        unique_students = IterableStructure.gnome_sort(unique_students, self.compare_elements)
        unique_students.reverse()
        return unique_students

    """
    STATISTICS 2
    """
    @staticmethod
    def grade_is_zero(element):
        if element.grade == 0:
            return True
        else:
            return False

    def date_passed(self, element):
        assignment = self.assignment_service.get_assignment_by_id(element.assignment_id)
        if assignment.deadline < date.today():
            return True
        else:
            return False

    def statistics_2(self):
        grades = self.grade_service.get_all()
        late_students_all = []
        filtered_by_grade = IterableStructure.filter(grades, lambda element: element.grade == 0)
        filtered_by_date = IterableStructure.filter(filtered_by_grade, self.date_passed)
        for index in range(len(filtered_by_date)):
            late_students_all.append(filtered_by_date[index].student_id)
        unique_late_students_all = unique(late_students_all)
        return unique_late_students_all

    """
    STATISTICS 3
    """
    def statistics_3(self):
        grades = self.grade_service.get_all()
        students_all = []
        for index in range(len(grades)):
            students_all.append(grades[index].student_id)
        assignments_all = self.assignment_service.get_all()
        best_students = []
        for index in range(len(students_all)):
            no_of_grades = 0
            sum_grades = 0
            for index1 in range(len(assignments_all)):
                for index2 in range(len(grades)):
                    if assignments_all[index1].assignment_id == grades[index2].assignment_id:
                        if grades[index2].grade == 0:
                            if assignments_all[index1].deadline < date.today():
                                if students_all[index] == grades[index2].student_id:
                                    no_of_grades += 1
                                    sum_grades += int(grades[index2].grade)
                        else:
                            if students_all[index] == grades[index2].student_id:
                                no_of_grades += 1
                                sum_grades += int(grades[index2].grade)
            if no_of_grades != 0:
                if sum_grades != 0:
                    avg_grade = round(sum_grades/no_of_grades, 2)
                    best_students.append((students_all[index], avg_grade))
                elif sum_grades == 0:
                    avg_grade = round(0)
                    best_students.append((students_all[index], avg_grade))
        best_students = unique(best_students)
        best_students = IterableStructure.gnome_sort(best_students, self.compare_elements)
        best_students.reverse()
        return best_students
