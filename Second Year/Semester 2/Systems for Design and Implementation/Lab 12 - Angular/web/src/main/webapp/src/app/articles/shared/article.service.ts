import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { map, Observable } from 'rxjs';
import { Article, ArticlesDTO } from './article.model';

@Injectable({
  providedIn: 'root'
})
export class ArticleService {
  private articlesUrl = 'http://localhost:8080/api/articles';

  constructor(private httpClient: HttpClient) { }

  getArticles(): Observable<ArticlesDTO> {
    return this.httpClient.get<ArticlesDTO>(this.articlesUrl);
  }

  saveArticle(article: Article): Observable<Article> {
    return this.httpClient.post<Article>(this.articlesUrl, article);
  }

  deleteArticle(articleId: number): Observable<any> {
    const url = `${this.articlesUrl}/${articleId}`;
    return this.httpClient.delete(url);
  }

  updateArticle(article: Article): Observable<Article> {
    const url = `${this.articlesUrl}/${article.id}`;
    return this.httpClient.put<Article>(url, article);
  }

  getArticle(id: number): Observable<any> {
    return this.getArticles().pipe(
      map(response => {
        let article;
        response.articles.forEach((elem: Article) => {
          if (elem.id === id) {
            article = elem;
          }
        })
        return article;
      })
    );
  }

  getFilteredByCategory(categoryId: number): Observable<ArticlesDTO> {
    const url = `${this.articlesUrl}/filter/${categoryId}`;
    return this.httpClient.get<ArticlesDTO>(url);
  }
}
