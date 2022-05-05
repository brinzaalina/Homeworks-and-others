import { Component, OnInit } from '@angular/core';
import { LogsService } from 'src/app/services/logs.service';

@Component({
  selector: 'app-remove-page',
  templateUrl: './remove-page.component.html',
  styleUrls: ['./remove-page.component.css']
})
export class RemovePageComponent implements OnInit {

  logs: Array<string[]> = [];
  pageCount = 0;
  page = 0;
  showNext = false;
  showPrevious = false;

  constructor(private logService: LogsService) { }

  ngOnInit(): void {
    console.log('ngOnInit called for deletePage');
    this.getNumberOfPages();
  }
  getNumberOfPages(): void {
    this.logService.getAllLogsForUser().subscribe(logs => this.pageCount = Math.ceil(logs.length / 4));
  }
  loadTable(page = 1): void {
    this.logService.getLogsPaginatedForUser(4, page)
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
  deleteLog(logId: string): void {
    if (logId.trim().length > 0) {
      if (confirm("Are you sure you want to delete the log with the id " + logId + "?")) {
        this.logService.deleteLog(logId)
          .subscribe(response => 
            {if(response !== "") 
              alert(response);
            else
              alert("Successful delete!");});
        this.getNumberOfPages();
        this.loadTable();
      }
    } else {
      alert("Empty id value!");
    }
  }
}
