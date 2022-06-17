import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';

@Component({
  selector: 'app-article-journalist',
  templateUrl: './article-journalist.component.html',
  styleUrls: ['./article-journalist.component.css']
})
export class ArticleJournalistComponent implements OnInit {

  constructor(private router: Router) { }

  ngOnInit(): void {
  }

  goBack() {
    this.router.navigate(['']);
  }
}
