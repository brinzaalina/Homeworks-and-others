import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { Journalist } from '../shared/journalist.model';
import { JournalistService } from '../shared/journalist.service';

@Component({
  selector: 'app-journalist-list',
  templateUrl: './journalist-list.component.html',
  styleUrls: ['./journalist-list.component.css']
})
export class JournalistListComponent implements OnInit {
  journalists: Array<Journalist> = [];
  filteredJournalists: Array<Journalist> = [];

  constructor(private journalistService: JournalistService, private router: Router) { }

  ngOnInit(): void {
    this.journalistService.getJournalists().subscribe(
      journalists => {this.journalists = journalists.journalists; console.log(journalists)}
    );
  }

  deleteJournalist(journalist: Journalist) {
    if(confirm("Are you sure you want to delete the selected journalist?")) {
      this.journalistService.deleteJournalist(journalist.id).subscribe(_ => this.journalists = this.journalists.filter(j => j.id !== journalist.id));
    }
  }

  updateJournalist(journalist: Journalist) {
    this.router.navigate(['/journalist-update', journalist.id]);
  }

  navigateToAddJournalist() {
    this.router.navigate(["/journalist-add"]);
  }

  filterJournalists(dob: string) {
    let date = dob.split("-");
    let formatedDob = date[2] + "-" + date[1] + "-" + date[0];
    this.journalistService.getJournalistsFilteredByDob(formatedDob).subscribe(journalists => this.filteredJournalists = journalists.journalists);
  }

}
