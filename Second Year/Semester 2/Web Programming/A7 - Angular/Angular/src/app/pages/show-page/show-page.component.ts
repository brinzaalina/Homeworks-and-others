import { Component, OnInit } from '@angular/core';
import { LogsService } from 'src/app/services/logs.service';

@Component({
  selector: 'app-show-page',
  templateUrl: './show-page.component.html',
  styleUrls: ['./show-page.component.css']
})
export class ShowPageComponent implements OnInit {

  logs: Array<string[]> | undefined;

  constructor(private logService: LogsService) { }

  ngOnInit(): void {
    console.log('ngOnInit called for filterPage');
  }
  loadTable(type: string, severity: string): void {
    this.logService.filterLogs(type, severity)
      .subscribe(filteredLogs => this.logs = filteredLogs);
  }
}
