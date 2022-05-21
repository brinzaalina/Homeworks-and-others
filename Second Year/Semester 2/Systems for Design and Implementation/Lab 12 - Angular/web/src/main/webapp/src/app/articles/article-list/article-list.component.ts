import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { Article } from '../shared/article.model';
import { ArticleService } from '../shared/article.service';

@Component({
  selector: 'app-article-list',
  templateUrl: './article-list.component.html',
  styleUrls: ['./article-list.component.css']
})
export class ArticleListComponent implements OnInit {
  articles: Array<Article> = [];
  filteredArticles: Array<Article> = [];
  filteredByTitleArticles: Array<Article> = [];

  constructor(private articleService: ArticleService, private router: Router) { }

  ngOnInit(): void {
    this.articleService.getArticles().subscribe(
      articles => this.articles = articles.articles
    )
  }

  deleteArticle(article: Article) {
    if(confirm("Are you sure you want to delete the selected article?")) {
      this.articleService.deleteArticle(article.id).subscribe(_ => this.articles = this.articles.filter(a => a.id !== article.id));
    }
  }

  updateArticle(article: Article) {
    this.router.navigate(['/article-update', article.id]);
  }

  navigateToAddArticle() {
    this.router.navigate(['/article-add']);
  }

  filterArticles(categoryId: string) {
    this.articleService.getFilteredByCategory(parseInt(categoryId)).subscribe(articles => this.filteredArticles = articles.articles);
  }

  filterByTitleArticles(titleSubstring: string) {
    this.filteredByTitleArticles = this.articles.filter(a => a.title.includes(titleSubstring));
  }

}
