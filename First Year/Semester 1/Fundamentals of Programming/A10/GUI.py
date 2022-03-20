import tkinter as tk
from datetime import date
from tkinter import simpledialog

from src.exceptions import RepositoryException, StudentException, AssignmentException, UndoRedoException


class GUI:
    """
      Implement the graphic user interface for add/list students
    """

    def __init__(self, student_service, assignment_service, grade_service, statistics, undo_redo_service):
        self.student_service = student_service
        self.assignment_service = assignment_service
        self.grade_service = grade_service
        self.statistics = statistics
        self.undo_redo_service = undo_redo_service
        self._window = tk.Tk()
        self._window.configure(bg='#A96DA3')
        for i in range(4):
            self._window.rowconfigure(i, minsize=75, weight=1)
            self._window.columnconfigure(i, minsize=50, weight=1)

    def start(self):
        self._window.title("Students Lab Assignment")
        btn_add_student = tk.Button(master=self._window, text='Add Student', bg='#FFDDE2', command=self.add_student)
        btn_add_student.grid(row=0, column=0, sticky='nsew', padx=10, pady=10)
        btn_add_assignment = tk.Button(master=self._window, text='Add Assignment', bg='#FFDDE2', command=self.add_assignment)
        btn_add_assignment.grid(row=1, column=0, sticky='nsew', padx=10, pady=10)
        btn_remove_student = tk.Button(master=self._window, text='Remove Student', bg='#FFDDE2', command=self.remove_student)
        btn_remove_student.grid(row=0, column=1, sticky='nsew', padx=10, pady=10)
        btn_remove_assignment = tk.Button(master=self._window, text='Remove Assignment', bg='#FFDDE2', command=self.remove_assignment)
        btn_remove_assignment.grid(row=1, column=1, sticky='nsew', padx=10, pady=10)
        btn_update_student = tk.Button(master=self._window, text='Update Student', bg='#FFDDE2', command=self.update_student)
        btn_update_student.grid(row=0, column=2, sticky='nsew', padx=10, pady=10)
        btn_update_assignment = tk.Button(master=self._window, text='Update Assignment', bg='#FFDDE2', command=self.update_assignment)
        btn_update_assignment.grid(row=1, column=2, sticky='nsew', padx=10, pady=10)
        btn_list_students = tk.Button(master=self._window, text='List Students', bg='#FFDDE2', command=self.list_students)
        btn_list_students.grid(row=2, column=0, sticky='nsew', padx=10, pady=10)
        btn_list_assignments = tk.Button(master=self._window, text='List Assignments', bg='#FFDDE2', command=self.list_assignments)
        btn_list_assignments.grid(row=2, column=1, sticky='nsew', padx=10, pady=10)
        btn_remove_assign = tk.Button(master=self._window, text='Remove an assigned assignment', bg='#FFDDE2', command=self.remove_an_assigned_assignment)
        btn_remove_assign.grid(row=3, column=0, sticky='nsew', padx=10, pady=10)
        btn_assignment_to_student = tk.Button(master=self._window, text='Give Assignment to Student', bg='#FFDDE2', command=self.give_assignment_to_student)
        btn_assignment_to_student.grid(row=3, column=1, sticky='nsew', padx=10, pady=10)
        btn_give_grade = tk.Button(master=self._window, text='Grade an Assignment', bg='#FFDDE2', command=self.grade_an_assignment)
        btn_give_grade.grid(row=3, column=2, sticky='nsew', padx=10, pady=10)
        btn_list_grades = tk.Button(master=self._window, text='List Assignments and Grades', bg='#FFDDE2', command=self.list_assignment_and_grades)
        btn_list_grades.grid(row=2, column=2, sticky='nsew', padx=10, pady=10)
        btn_statistic_one = tk.Button(master=self._window, text='Statistic One', bg='#FFDDE2', command=self.statistics_1)
        btn_statistic_one.grid(row=4, column=0, sticky='nsew', padx=10, pady=10)
        btn_statistic_two = tk.Button(master=self._window, text='Statistic Two', bg='#FFDDE2', command=self.statistics_2)
        btn_statistic_two.grid(row=4, column=1, sticky='nsew', padx=10, pady=10)
        btn_statistic_three = tk.Button(master=self._window, text='Statistic Three', bg='#FFDDE2', command=self.statistics_3)
        btn_statistic_three.grid(row=4, column=2, sticky='nsew', padx=10, pady=10)
        btn_exit = tk.Button(master=self._window, text='Exit', bg='#FFDDE2', command=self._window.destroy)
        btn_exit.grid(row=6, column=1, sticky='nsew', padx=10, pady=10)
        btn_undo = tk.Button(master=self._window, text='Undo', bg='#FFDDE2', command=self.undo)
        btn_undo.grid(row=5, column=0, sticky='nsew', padx=10, pady=10)
        btn_redo = tk.Button(master=self._window, text='Redo', bg='#FFDDE2',command=self.redo)
        btn_redo.grid(row=5, column=2, sticky='nsew', padx=10, pady=10)
        btn_filter_sort = tk.Button(master=self._window, text="Grades>=5, sorted", bg='#FFDDE2', command=self.grades_five)
        btn_filter_sort.grid(row=5, column=1, sticky='nsew', padx=10, pady=10)
        self._window.mainloop()

    @staticmethod
    def unique(list_):
        list_set = set(list_)
        unique_list = (list(list_set))
        return unique_list

    def add_student(self):
        try:
            text1 = simpledialog.askstring(title="ID", prompt="Enter student id:")
            text2 = simpledialog.askstring(title="NAME", prompt="Enter student name:")
            text3 = simpledialog.askstring(title="GROUP", prompt="Enter student group:")
            self.student_service.add(text1, text2, int(text3))
        except RepositoryException as re:
            self.window2 = tk.Tk()
            self.window2.configure(bg='#FFDDE2')
            label = tk.Label(master=self.window2, text=str(re), bg='#FFDDE2')
            label.pack()
        except StudentException as se:
            self.window2 = tk.Tk()
            self.window2.configure(bg='#FFDDE2')
            label = tk.Label(master=self.window2, text=str(se), bg='#FFDDE2')
            label.pack()
        except ValueError as ve:
            self.window2 = tk.Tk()
            self.window2.configure(bg='#FFDDE2')
            label = tk.Label(master=self.window2, text=str(ve), bg='#FFDDE2')
            label.pack()

    def remove_student(self):
        try:
            text1 = simpledialog.askstring(title="STUDENT TO REMOVE", prompt="Enter student id:")
            self.student_service.remove(text1)
            self.grade_service.remove_by_student(text1)
        except RepositoryException as re:
            self.window2 = tk.Tk()
            self.window2.configure(bg='#FFDDE2')
            label = tk.Label(master=self.window2, text=str(re), bg='#FFDDE2')
            label.pack()
        except ValueError as ve:
            self.window2 = tk.Tk()
            self.window2.configure(bg='#FFDDE2')
            label = tk.Label(master=self.window2, text=str(ve), bg='#FFDDE2')
            label.pack()

    def update_student(self):
        try:
            text1 = simpledialog.askstring(title="ID", prompt="Enter student id:")
            text2 = simpledialog.askstring(title="NAME", prompt="Enter student new name:")
            text3 = simpledialog.askstring(title="GROUP", prompt="Enter student new group:")
            self.student_service.update(text1, text2, int(text3))
        except RepositoryException as re:
            self.window2 = tk.Tk()
            self.window2.configure(bg='#FFDDE2')
            label = tk.Label(master=self.window2, text=str(re), bg='#FFDDE2')
            label.pack()
        except ValueError as ve:
            self.window2 = tk.Tk()
            self.window2.configure(bg='#FFDDE2')
            label = tk.Label(master=self.window2, text=str(ve), bg='#FFDDE2')
            label.pack()
        except StudentException as se:
            self.window2 = tk.Tk()
            self.window2.configure(bg='#FFDDE2')
            label = tk.Label(master=self.window2, text=str(se), bg='#FFDDE2')
            label.pack()

    def add_assignment(self):
        try:
            text1 = simpledialog.askstring(title="ID", prompt="Enter assignment id:")
            text2 = simpledialog.askstring(title="DESCRIPTION", prompt="Enter description:")
            text3 = simpledialog.askstring(title="DEADLINE YEAR", prompt="Enter deadline year:")
            text4 = simpledialog.askstring(title="DEADLINE MONTH", prompt="Enter deadline month:")
            text5 = simpledialog.askstring(title="DEADLINE DAY", prompt="Enter deadline day:")
            self.assignment_service.add(text1, text2, date(int(text3), int(text4), int(text5)))
        except RepositoryException as re:
            self.window2 = tk.Tk()
            self.window2.configure(bg='#FFDDE2')
            label = tk.Label(master=self.window2, text=str(re), bg='#FFDDE2')
            label.pack()
        except ValueError as ve:
            self.window2 = tk.Tk()
            self.window2.configure(bg='#FFDDE2')
            label = tk.Label(master=self.window2, text=str(ve), bg='#FFDDE2')
            label.pack()
        except AssignmentException as ae:
            self.window2 = tk.Tk()
            self.window2.configure(bg='#FFDDE2')
            label = tk.Label(master=self.window2, text=str(ae), bg='#FFDDE2')
            label.pack()


    def remove_assignment(self):
        try:
            text1 = simpledialog.askstring(title="ASSIGNMENT TO REMOVE", prompt="Enter assignment id:")
            self.assignment_service.remove(text1)
            self.grade_service.remove_by_assignment(text1)
        except RepositoryException as re:
            self.window2 = tk.Tk()
            self.window2.configure(bg='#FFDDE2')
            label = tk.Label(master=self.window2, text=str(re), bg='#FFDDE2')
            label.pack()
        except ValueError as ve:
            self.window2 = tk.Tk()
            self.window2.configure(bg='#FFDDE2')
            label = tk.Label(master=self.window2, text=str(ve), bg='#FFDDE2')
            label.pack()

    def update_assignment(self):
        try:
            text1 = simpledialog.askstring(title="ID", prompt="Enter assignment id:")
            text2 = simpledialog.askstring(title="DESCRIPTION", prompt="Enter new description:")
            text3 = simpledialog.askstring(title="DEADLINE YEAR", prompt="Enter new deadline year:")
            text4 = simpledialog.askstring(title="DEADLINE MONTH", prompt="Enter new deadline month:")
            text5 = simpledialog.askstring(title="DEADLINE DAY", prompt="Enter new deadline day:")
            self.assignment_service.update(text1, text2, date(int(text3), int(text4), int(text5)))
        except ValueError as ve:
            self.window2 = tk.Tk()
            self.window2.configure(bg='#FFDDE2')
            label = tk.Label(master=self.window2, text=str(ve), bg='#FFDDE2')
            label.pack()
        except RepositoryException as re:
            self.window2 = tk.Tk()
            self.window2.configure(bg='#FFDDE2')
            label = tk.Label(master=self.window2, text=str(re), bg='#FFDDE2')
            label.pack()
        except AssignmentException as ae:
            self.window2 = tk.Tk()
            self.window2.configure(bg='#FFDDE2')
            label = tk.Label(master=self.window2, text=str(ae), bg='#FFDDE2')
            label.pack()

    def list_students(self):
        try:
            self.window1 = tk.Tk()
            self.window1.configure(bg='#FFDDE2')
            students = self.student_service.get_all()
            for student in students:
                label = tk.Label(master=self.window1, text=str(student), anchor='e', justify=tk.LEFT, bg='#FFDDE2')
                label.pack()
        except RepositoryException as re:
            self.window2 = tk.Tk()
            self.window2.configure(bg='#FFDDE2')
            label = tk.Label(master=self.window2, text=str(re), bg='#FFDDE2')
            label.pack()

    def list_assignments(self):
        try:
            self.window1 = tk.Tk()
            self.window1.configure(bg='#FFDDE2')
            assignments = self.assignment_service.get_all()
            for assignment in assignments:
                label = tk.Label(master=self.window1, text=str(assignment), anchor='e', justify=tk.LEFT, bg='#FFDDE2')
                label.pack()
        except RepositoryException as re:
            self.window2 = tk.Tk()
            self.window2.configure(bg='#FFDDE2')
            label = tk.Label(master=self.window2, text=str(re), bg='#FFDDE2')
            label.pack()

    def list_assignment_and_grades(self):
        try:
            self.window1 = tk.Tk()
            self.window1.configure(bg='#FFDDE2')
            grades = self.grade_service.get_all()
            for grade in grades:
                label = tk.Label(master=self.window1, text=str(grade), anchor='e', justify=tk.LEFT, bg='#FFDDE2')
                label.pack()
        except RepositoryException as re:
            self.window2 = tk.Tk()
            self.window2.configure(bg='#FFDDE2')
            label = tk.Label(master=self.window2, text=str(re), bg='#FFDDE2')
            label.pack()

    def remove_an_assigned_assignment(self):
        students = self.student_service.get_all()
        student_ids = []
        for index in range(len(students)):
            student_ids.append(students[index].student_id)
        assignments = self.assignment_service.get_all()
        assignment_ids = []
        for index in range(len(assignments)):
            assignment_ids.append(assignments[index].assignment_id)
        student_id = simpledialog.askstring(title="STUDENT ID", prompt="Enter the id of the student: ")
        assignment_id = simpledialog.askstring(title="ASSIGNMENT ID", prompt="What assignment do you want to remove?")
        try:
            if student_id in student_ids:
                if assignment_id in assignment_ids:
                    self.grade_service.remove(student_id, assignment_id)
                else:
                    raise RepositoryException("No such assignment id in the list!")
            else:
                raise RepositoryException("No such student id in the list!")
        except RepositoryException as re:
            self.window2 = tk.Tk()
            self.window2.configure(bg='#FFDDE2')
            label = tk.Label(master=self.window2, text=str(re), bg='#FFDDE2')
            label.pack()

    def give_assignment_to_student(self):
        students = self.student_service.get_all()
        student_ids = []
        for index in range(len(students)):
            student_ids.append(students[index].student_id)
        assignments = self.assignment_service.get_all()
        assignment_ids = []
        for index in range(len(assignments)):
            assignment_ids.append(assignments[index].assignment_id)
        assignment_id = simpledialog.askstring(title="ASSIGNMENT ID", prompt="What assignment do you want to give?")
        student_id = simpledialog.askstring(title="STUDENT ID", prompt="Enter the id of the student: ")
        try:
            if student_id in student_ids:
                if assignment_id in assignment_ids:
                    self.grade_service.add(student_id, assignment_id, 0)
                else:
                    raise RepositoryException("No such assignment id in the list!")
            else:
                raise RepositoryException("No such student id in the list!")
        except RepositoryException as re:
            self.window2 = tk.Tk()
            self.window2.configure(bg='#FFDDE2')
            label = tk.Label(master=self.window2, text=str(re), bg='#FFDDE2')
            label.pack()

    def grade_an_assignment(self):
        try:
            grades = self.grade_service.get_all()
            students = []
            for index in range(len(grades)):
                students.append(grades[index].student_id)
            unique_students = self.unique(students)
            if len(unique_students) == 0:
                raise RepositoryException("No student with assignments.")
            student_id = simpledialog.askstring(title="STUDENT ID", prompt="Enter the id of the student you want to grade: ")
            if student_id not in unique_students:
                raise RepositoryException("Invalid student id, there's no student with this id with assignments!")
            else:
                assignments = []
                grade_type = []
                for index in range((len(grades))):
                    if grades[index].student_id == student_id:
                        if grades[index].grade == 0:
                            assignments.append(grades[index].assignment_id)
                            grade_type.append({'assignment': grades[index].assignment_id, 'status': "ungraded"})
                        else:
                            assignments.append(grades[index].assignment_id)
                            grade_type.append({'assignment': grades[index].assignment_id, 'status': "graded"})
                for index in range(len(assignments)):
                    self.window3 = tk.Tk()
                    self.window3.configure(bg='#FFDDE2')
                    label = tk.Label(master=self.window3, text=str(assignments[index] + ", " + grade_type[index]['status']), bg='#FFDDE2')
                    label.pack()
            assignment_id = simpledialog.askstring(title="ASSIGNMENT ID", prompt="Enter the id of the assignment you want to grade: ")
            if assignment_id in assignments:
                for index_type in range(len(grade_type)):
                    if grade_type[index_type]['assignment'] == assignment_id:
                        if grade_type[index_type]['status'] == "graded":
                            raise RepositoryException("This assignment has already been graded.")
                grade = simpledialog.askstring(title="GRADE", prompt="Enter the grade: ")
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
        except RepositoryException as re:
            self.window2 = tk.Tk()
            self.window2.configure(bg='#FFDDE2')
            label = tk.Label(master=self.window2, text=str(re), bg='#FFDDE2')
            label.pack()
        except ValueError as ve:
            self.window2 = tk.Tk()
            self.window2.configure(bg='#FFDDE2')
            label = tk.Label(master=self.window2, text=str(ve), bg='#FFDDE2')
            label.pack()

    def statistics_1(self):
        self.windowstat1 = tk.Tk()
        self.windowstat1.configure(bg='#FFDDE2')
        label_title = tk.Label(master=self.windowstat1, text="--All students who received a given assignment, ordered by average grade for that assignment--", bg='#FFDDE2')
        label_title.pack()
        unique_assignments = self.statistics.get_unique_assignments()
        for index in range(len(unique_assignments)):
            label1 = tk.Label(master=self.windowstat1, text="ASSIGNMENT: {}".format(unique_assignments[index]), bg='#FFDDE2')
            label1.pack()
            label2 = tk.Label(master=self.windowstat1, text="STUDENT ID ---------- GRADE", bg='#FFDDE2')
            label2.pack()
            unique_students = self.statistics.statistics_1(unique_assignments[index])
            for index1 in range(len(unique_students)):
                if unique_students[index1][1] != 0:
                    label = tk.Label(master=self.windowstat1, text=str(unique_students[index1][0] + "     ----------   " + str(unique_students[index1][1])), bg='#FFDDE2')
                    label.pack()
                elif unique_students[index1][1] == 0:
                    label = tk.Label(master=self.windowstat1, text=str(unique_students[index1][0] + "     ---------- ungraded"), bg='#FFDDE2')
                    label.pack()

    def statistics_2(self):
        self.windowstat2 = tk.Tk()
        self.windowstat2.configure(bg='#FFDDE2')
        label_title = tk.Label(master=self.windowstat2, text="--All students who are late in handing in at least one assignment--", bg='#FFDDE2')
        label_title.pack()
        unique_late_students_all = self.statistics.statistics_2()
        if len(unique_late_students_all) != 0:
            for index in range(len(unique_late_students_all)):
                label = tk.Label(master=self.windowstat2, text=str(unique_late_students_all[index]), bg='#FFDDE2')
                label.pack()
        else:
            label_empty = tk.Label(master=self.windowstat2, text="No students that are late for all the given assignments.", bg='#FFDDE2')
            label_empty.pack()

    def statistics_3(self):
        self.windowstat3 = tk.Tk()
        self.windowstat3.configure(bg='#FFDDE2')
        label_title = tk.Label(master=self.windowstat3, text="--Students with the best school situation, sorted in descending order of the average grade received for all assignments--", bg='#FFDDE2')
        label_title.pack()
        best_students = self.statistics.statistics_3()
        for index in range(len(best_students)):
            if best_students[index][1] != 0:
                label = tk.Label(master=self.windowstat3, text=str("Student ID: {}, average grade: {}".format(best_students[index][0], best_students[index][1])), bg='#FFDDE2')
                label.pack()
            else:
                label = tk.Label(master=self.windowstat3, text=str("Student ID: {}, this student is late for all assignments, average grade is 0.".format(best_students[index][0])), bg='#FFDDE2')
                label.pack()

    def undo(self):
        try:
            self.undo_redo_service.undo()
        except UndoRedoException as ure:
            self.window2 = tk.Tk()
            self.window2.configure(bg='#FFDDE2')
            label = tk.Label(master=self.window2, text=str(ure), bg='#FFDDE2')
            label.pack()

    def redo(self):
        try:
            self.undo_redo_service.redo()
        except UndoRedoException as ure:
            self.window2 = tk.Tk()
            self.window2.configure(bg='#FFDDE2')
            label = tk.Label(master=self.window2, text=str(ure), bg='#FFDDE2')
            label.pack()

    def grades_five(self):
        self.window1 = tk.Tk()
        self.window1.configure(bg='#FFDDE2')
        passing_grades_sorted = self.grade_service.filter_by_grade()
        for grade in passing_grades_sorted:
            label = tk.Label(master=self.window1, text=str(grade), anchor='e', justify=tk.LEFT, bg='#FFDDE2')
            label.pack()
