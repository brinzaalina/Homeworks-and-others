from src.services.service import Service
from src.ui.console import Console

service = Service()
console = Console(service)
console.start_ui()
