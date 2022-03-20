"""
--START MODULE--
"""
from src.GUI import GUI
from src.repository.repo import RepositoryStudents, RepositoryAssignments, RepositoryGrade
from src.repository.repo_pickle import StudentRepositoryPickle, AssignmentRepositoryPickle, GradeRepositoryPickle
from src.repository.repo_text import StudentRepositoryTextFile, AssignmentRepositoryTextFile, GradesRepositoryTextFile
from src.services.service import StudentService, AssignmentService, GradeService
from src.services.statistics import Statistics
from src.services.undo_redo_service import UndoRedoService
from src.ui.ui import UI
from src.validators.validator import StudentValidator, AssignmentValidator

with open("settings.properties", "r") as f:
    mode = f.readline()
    mode = mode.split()
    mode = mode[2]

    if mode == "inmemory":
        student_repo = RepositoryStudents()
        assignment_repo = RepositoryAssignments()
        grade_repo = RepositoryGrade()
        f.readline()
        f.readline()
        f.readline()
        type = f.readline()
        type = type.split()
        type = type[2]
        if type == "GUI":
            student_validator = StudentValidator
            assignment_validator = AssignmentValidator
            undo_redo_service = UndoRedoService()
            grade_service = GradeService(student_repo, assignment_repo, grade_repo, undo_redo_service)
            student_service = StudentService(student_repo, student_validator, undo_redo_service, grade_service)
            assignment_service = AssignmentService(assignment_repo, assignment_validator, undo_redo_service,
                                                   grade_service)
            statistics = Statistics(grade_service, assignment_service, student_service)
            student_service.initialise()
            assignment_service.initialise()
            grade_service.initialise()
            console = GUI(student_service, assignment_service, grade_service, statistics, undo_redo_service)
        else:
            student_validator = StudentValidator
            assignment_validator = AssignmentValidator
            undo_redo_service = UndoRedoService()
            grade_service = GradeService(student_repo, assignment_repo, grade_repo, undo_redo_service)
            student_service = StudentService(student_repo, student_validator, undo_redo_service, grade_service)
            assignment_service = AssignmentService(assignment_repo, assignment_validator, undo_redo_service,
                                                   grade_service)
            statistics = Statistics(grade_service, assignment_service, student_service)
            student_service.initialise()
            assignment_service.initialise()
            grade_service.initialise()
            console = UI(student_service, assignment_service, grade_service, statistics, undo_redo_service)
    elif mode == "binaryfile":
        student_file = f.readline()
        student_file = student_file.split()
        student_file = student_file[2]
        student_repo = StudentRepositoryPickle(student_file)

        assignment_file = f.readline()
        assignment_file = assignment_file.split()
        assignment_file = assignment_file[2]
        assignment_repo = AssignmentRepositoryPickle(assignment_file)

        grade_file = f.readline()
        grade_file = grade_file.split()
        grade_file = grade_file[2]
        grade_repo = GradeRepositoryPickle(grade_file)

        type = f.readline()
        type = type.split()
        type = type[2]
        if type == "GUI":
            student_validator = StudentValidator
            assignment_validator = AssignmentValidator
            undo_redo_service = UndoRedoService()
            grade_service = GradeService(student_repo, assignment_repo, grade_repo, undo_redo_service)
            student_service = StudentService(student_repo, student_validator, undo_redo_service, grade_service)
            assignment_service = AssignmentService(assignment_repo, assignment_validator, undo_redo_service,
                                                   grade_service)
            statistics = Statistics(grade_service, assignment_service, student_service)
            student_service.initialise()
            assignment_service.initialise()
            grade_service.initialise()
            console = GUI(student_service, assignment_service, grade_service, statistics, undo_redo_service)
        else:
            student_validator = StudentValidator
            assignment_validator = AssignmentValidator
            undo_redo_service = UndoRedoService()
            grade_service = GradeService(student_repo, assignment_repo, grade_repo, undo_redo_service)
            student_service = StudentService(student_repo, student_validator, undo_redo_service, grade_service)
            assignment_service = AssignmentService(assignment_repo, assignment_validator, undo_redo_service,
                                                   grade_service)
            statistics = Statistics(grade_service, assignment_service, student_service)
            student_service.initialise()
            assignment_service.initialise()
            grade_service.initialise()
            console = UI(student_service, assignment_service, grade_service, statistics, undo_redo_service)
    else:
        student_file = f.readline()
        student_file = student_file.split()
        student_file = student_file[2]
        student_repo = StudentRepositoryTextFile(student_file)

        assignment_file = f.readline()
        assignment_file = assignment_file.split()
        assignment_file = assignment_file[2]
        assignment_repo = AssignmentRepositoryTextFile(assignment_file)

        grade_file = f.readline()
        grade_file = grade_file.split()
        grade_file = grade_file[2]
        grade_repo = GradesRepositoryTextFile(grade_file)

        type = f.readline()
        type = type.split()
        type = type[2]
        if type == "GUI":
            student_validator = StudentValidator
            assignment_validator = AssignmentValidator
            undo_redo_service = UndoRedoService()
            grade_service = GradeService(student_repo, assignment_repo, grade_repo, undo_redo_service)
            student_service = StudentService(student_repo, student_validator, undo_redo_service, grade_service)
            assignment_service = AssignmentService(assignment_repo, assignment_validator, undo_redo_service,
                                                   grade_service)
            statistics = Statistics(grade_service, assignment_service, student_service)
            student_service.initialise()
            assignment_service.initialise()
            grade_service.initialise()
            console = GUI(student_service, assignment_service, grade_service, statistics, undo_redo_service)
        else:
            student_validator = StudentValidator
            assignment_validator = AssignmentValidator
            undo_redo_service = UndoRedoService()
            grade_service = GradeService(student_repo, assignment_repo, grade_repo, undo_redo_service)
            student_service = StudentService(student_repo, student_validator, undo_redo_service, grade_service)
            assignment_service = AssignmentService(assignment_repo, assignment_validator, undo_redo_service,
                                                   grade_service)
            statistics = Statistics(grade_service, assignment_service, student_service)
            student_service.initialise()
            assignment_service.initialise()
            grade_service.initialise()
            console = UI(student_service, assignment_service, grade_service, statistics, undo_redo_service)

console.start()
