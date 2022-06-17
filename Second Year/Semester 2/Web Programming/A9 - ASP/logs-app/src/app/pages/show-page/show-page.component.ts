import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { Log } from 'src/app/models/log.model';
import { LogsService } from 'src/app/services/logs.service';

@Component({
  selector: 'app-show-page',
  templateUrl: './show-page.component.html',
  styleUrls: ['./show-page.component.css']
})
export class ShowPageComponent implements OnInit {

  logs: Array<Log> | undefined;

  constructor(private logService: LogsService, private router: Router) { }

  ngOnInit(): void {
    console.log('ngOnInit called for filterPage');
    if (localStorage.getItem("token") == null)
      this.router.navigate(["/login"]);
  }
  loadTable(type: string, severity: string): void {
    this.logService.filterLogs(type, severity)
      .subscribe(filteredLogs => this.logs = filteredLogs);
  }
}
