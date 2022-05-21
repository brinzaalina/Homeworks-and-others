import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { Journalist } from '../shared/journalist.model';
import { JournalistService } from '../shared/journalist.service';

@Component({
  selector: 'app-journalist-add',
  templateUrl: './journalist-add.component.html',
  styleUrls: ['./journalist-add.component.css']
})
export class JournalistAddComponent implements OnInit {

  constructor(private service: JournalistService, private router: Router) { }

  ngOnInit(): void {
  }

  saveJournalist(lastName: string, firstName: string, email: string, dob: string) {
    this.service.saveJournalist(new Journalist(0, lastName, firstName, email, new Date(dob))).subscribe(_ => this.router.navigate(['/journalists']));
  }

  onCancel(): void {
    if(confirm("Are you sure you want to cancel?")) {
      this.router.navigate(['/journalists']);
    }
  }

}
