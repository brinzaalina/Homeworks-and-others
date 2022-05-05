import { Component, OnInit } from '@angular/core';
import { LogsService } from 'src/app/services/logs.service';

@Component({
  selector: 'app-add-page',
  templateUrl: './add-page.component.html',
  styleUrls: ['./add-page.component.css']
})
export class AddPageComponent implements OnInit {
  logs: Array<string[]> = [];
  pageCount = 0;
  page = 0;
  showNext = false;
  showPrevious = false;

  constructor(private logService: LogsService) { }

  ngOnInit(): void {
    console.log('ngOnInit called for addPage');
    this.getNumberOfPages();
  }

  getNumberOfPages(): void {
    this.logService.getAllLogs().subscribe(logs => this.pageCount = Math.ceil(logs.length / 4));
    console.log(this.pageCount);
  }

  loadTable(page = 1): void {
    this.logService.getLogsPaginated(4, page)
      .subscribe(logsRes => this.logs = logsRes);
    this.page = page;
    this.showNext = false;
    this.showPrevious = false;
    if (this.pageCount > 0 && page < this.pageCount) {
      this.showNext = true;
    }
    if (page > 1) {
      this.showPrevious = true;
    }
  }

  goToPreviousPage(): void {
    if (this.page > 1) {
      this.loadTable(this.page - 1);
    }
  }

  goToNextPage(): void {
    if (this.page < this.pageCount) {
      this.loadTable(this.page + 1);
    }
  }

  addLog(type: string, severity: string, date: string, message: string): void {
    if (type.trim().length > 0 && severity.trim().length > 0 && date.trim().length > 0 && message.trim().length > 0) {
      this.logService.addLog(type, severity, date, message)
        .subscribe(response => console.log(response));
      this.getNumberOfPages();
      window.location.reload();
    } else {
      alert("Please enter valid data in all fields!");
    }
}
}
