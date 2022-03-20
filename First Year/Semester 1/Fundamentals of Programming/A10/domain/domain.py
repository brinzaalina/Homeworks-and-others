"""
This is the domain, where we can find the following classes: exceptions, entities(student, assignment, grade)
"""


class Student:
    """
    Class for the student entity.
    """
    def __init__(self, student_id, name, group):
        """
        Initialize the values for the student attributes.
        :param student_id: the id of the student
        :param name: the name of the student
        :param group: the group in which the student is
        """
        self._student_id = student_id
        self._name = name
        self._group = group

    @property
    def student_id(self):
        """
        Getter method
        :return: student id
        """
        return self._student_id

    @property
    def name(self):
        """
        Getter method
        :return: student name
        """
        return self._name

    @name.setter
    def name(self, value):
        """
        Setter method
        :param value: the name given by the user
        :return: -
        """
        self._name = value

    @property
    def group(self):
        """
        Getter method
        :return: student group
        """
        return self._group

    @group.setter
    def group(self, value):
        """
        Setter method
        :param value: the group given by the user
        :return: -
        """
        self._group = value

    def __str__(self):
        """
        Turn into str an entity.
        :return: the entity in str format
        """
        return "ID: {} , Name: {}, from group {}".format(self.student_id, self.name, self.group)

    def __eq__(self, other):
        return self.student_id == other.student_id


class Assignment:
    """
    Class for the assignment entity.
    """
    def __init__(self, assignment_id, description, deadline):
        """
        Initialize the values of the assignment entity
        :param assignment_id: the id of the assignment
        :param description: the description of the assignment
        :param deadline: the deadline of the assignment
        """
        self._assignment_id = assignment_id
        self._description = description
        self._deadline = deadline

    @property
    def assignment_id(self):
        """
        Getter method
        :return: the id of the assignment
        """
        return self._assignment_id

    @property
    def description(self):
        """
        Getter method
        :return: the description of the assignment
        """
        return self._description

    @description.setter
    def description(self, value):
        """
        Setter method
        :param value: the value given by the user
        :return: -
        """
        self._description = value

    @property
    def deadline(self):
        """
        Getter method
        :return: the deadline of the assignment
        """
        return self._deadline

    @deadline.setter
    def deadline(self, value):
        """
        Setter method
        :param value: the value given by the user
        :return: -
        """
        self._deadline = value

    def __str__(self):
        """
        Turns into str an assignment entity.
        :return: the assignment in str format
        """
        return "Assignment {} -> description: {} with deadline: {}".format(self.assignment_id, self.description,
                                                                           self.deadline)

    def __eq__(self, other):
        if other is not None:
            return self.assignment_id == other.assignment_id


class Grade:
    """
    Grade entity to create an assignment which can be graded.
    """
    def __init__(self, student_id, assignment_id, grade):
        """
        Initialize the parameters of an entity from the class.
        :param student_id: the id of the student
        :param assignment_id: the id of the assignment
        :param grade: grade (0 if not graded, else if graded)
        """
        self._student_id = student_id
        self._assignment_id = assignment_id
        self._grade = grade

    @property
    def student_id(self):
        return self._student_id

    @property
    def assignment_id(self):
        return self._assignment_id

    @property
    def grade(self):
        return self._grade

    @grade.setter
    def grade(self, value):
        self._grade = value

    def __str__(self):
        """
        Str method for an entity, with 2 different types.
        :return: One type if the assignment is not graded, the other one if graded.
        """
        if self.grade == 0:
            return "Assigned to student {} the assignment {}".format(self.student_id, self.assignment_id)
        else:
            return "The grade for student {} for the assignment {} is {}".format(self.student_id, self.assignment_id,
                                                                                 float(self.grade))

    def __eq__(self, other):
        return self.student_id == other.student_id and self.assignment_id == other.assignment_id
