"""
Statistics module
Implemented this because I didn't want to have a crowded service or ui
"""
from datetime import date


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
    def take_second(elem):
        return float(elem[1])

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
        unique_students = unique(students)
        unique_students.sort(reverse=True, key=self.take_second)
        return unique_students

    """
    STATISTICS 2
    """
    def statistics_2(self):
        grades = self.grade_service.get_all()
        late_students_all = []
        for index in range(len(grades)):
            if grades[index].grade == 0:
                assignment = self.assignment_service.get_assignment_by_id(grades[index].assignment_id)
                if assignment.deadline < date.today():
                    late_students_all.append(grades[index].student_id)
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
        best_students.sort(reverse=True, key=self.take_second)
        return best_students
