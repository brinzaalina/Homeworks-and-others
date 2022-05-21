import { Component, Input, OnInit } from '@angular/core';
import { ActivatedRoute, Params, Router } from '@angular/router';
import { switchMap } from 'rxjs';
import { Journalist } from '../shared/journalist.model';
import { JournalistService } from '../shared/journalist.service';

@Component({
  selector: 'app-journalist-update',
  templateUrl: './journalist-update.component.html',
  styleUrls: ['./journalist-update.component.css']
})
export class JournalistUpdateComponent implements OnInit {
  @Input() journalist: Journalist = new Journalist();
  dob: string = "";

  constructor(private service: JournalistService, private router: Router, private route: ActivatedRoute) { }

  ngOnInit(): void {
    this.route.params
        .pipe(switchMap((params: Params) => this.service.getJournalist(+params['id'])))
        .subscribe(journalist =>  {this.journalist = journalist; 
          var date = new Date(journalist.dob); 
          var month = date.getMonth() + 1;
          var monthStr = month.toString();
          if (month < 10) {
            monthStr = "0" + monthStr;
          }
          var dayStr = date.getDate().toString();
          if(date.getDate() < 10) {
            dayStr = "0" + dayStr;
          }
          this.dob = date.getFullYear() + '-' + monthStr + '-' + dayStr});
  }

  saveJournalistUpdates() {
    this.journalist.dob = new Date(this.dob);
    this.service.updateJournalist(this.journalist).subscribe(_ => this.router.navigate(['/journalists']));
  }

  onCancel(): void {
    if(confirm("Are you sure you want to cancel?")) {
      this.router.navigate(['/journalists']);
    }
  }

}
