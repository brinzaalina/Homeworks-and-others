class StudentException(Exception):
    """
    Exception for the Student class.
    """
    def __init__(self, msg=''):
        self._msg = msg

    def __str__(self):
        return self._msg



class AssignmentException(Exception):
    """
    Exception for the Assignment class.
    """
    def __init__(self, msg=''):
        self._msg = msg

    def __str__(self):
        return self._msg


class RepositoryException(Exception):
    """
    Exception for the Repository class.
    """
    def __init__(self, msg=''):
        self._msg = msg

    def __str__(self):
        return self._msg


class UndoRedoException(Exception):
    def __init__(self, msg=''):
        self._msg = msg

    def __str__(self):
        return self._msg