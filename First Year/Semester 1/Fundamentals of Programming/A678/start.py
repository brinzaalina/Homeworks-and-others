"""
--START MODULE--
"""
from src.repository.repo import RepositoryStudents, RepositoryAssignments, RepositoryGrade
from src.services.service import StudentService, AssignmentService, GradeService
from src.services.statistics import Statistics
from src.services.undo_redo_service import UndoRedoService
from src.ui.ui import UI
from src.validators.validator import StudentValidator, AssignmentValidator

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
console = UI(student_service, assignment_service, grade_service, statistics, undo_redo_service)
console.start_ui()
