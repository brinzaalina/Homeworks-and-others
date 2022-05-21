import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { Article } from '../shared/article.model';
import { ArticleService } from '../shared/article.service';

@Component({
  selector: 'app-article-add',
  templateUrl: './article-add.component.html',
  styleUrls: ['./article-add.component.css']
})
export class ArticleAddComponent implements OnInit {

  constructor(private articleService: ArticleService, private router: Router) { }

  ngOnInit(): void {
  }

  saveArticle(title: string, text: string, categoryId: string) {
    this.articleService.saveArticle(new Article(0, title, text, parseInt(categoryId))).subscribe(_ => this.router.navigate(['/articles']));
  }

  onCancel(): void {
    if(confirm("Are you sure you want to cancel?")) {
      this.router.navigate(['/articles']);
    }
  }
}
