from src.exceptions import UndoRedoException


class UndoRedoService:
    def __init__(self):
        self._history = []
        self._index = -1

    def record(self, operation):
        self._history = self._history[0:self._index + 1]
        self._history.append(operation)
        self._index += 1

    def undo(self):
        if self._index == -1:
            raise UndoRedoException("No operation to undo!")
        self._history[self._index].undo()
        self._index -= 1
        return True

    def redo(self):
        if self._index + 1 == len(self._history):
            raise UndoRedoException("No operation to redo!")
        self._index += 1
        self._history[self._index].redo()
        return True


class Operation:
    def __init__(self, function_call_undo, function_call_redo):
        self._function_call_undo = function_call_undo
        self._function_call_redo = function_call_redo

    def undo(self):
        self._function_call_undo()

    def redo(self):
        self._function_call_redo()


class FunctionCall:
    def __init__(self, function_name, *function_params):
        self._function_name = function_name
        self._function_params = function_params

    def call(self):
        return self._function_name(*self._function_params)

    def __call__(self):
        return self.call()
