import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';

@Component({
  selector: 'app-journalists',
  templateUrl: './journalists.component.html',
  styleUrls: ['./journalists.component.css']
})
export class JournalistsComponent implements OnInit {

  constructor(private router: Router) { }

  ngOnInit(): void {
  }

  goBack() {
    this.router.navigate(['']);
  }

}
