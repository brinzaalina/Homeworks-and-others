import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Observable } from 'rxjs';
import { Journalist } from 'src/app/journalists/shared/journalist.model';
import { ArticleJournalistPrimaryKey } from './article-journalist-key.model';
import { ArticleJournalist, ArticleJournalistsDTO } from './article-journalist.model';

@Injectable({
  providedIn: 'root'
})
export class ArticleJournalistService {
  private articleJournalistUrl = 'http://localhost:8080/api/articles-journalists';

  constructor(private httpClient: HttpClient) { }

  getArticleJournalists(): Observable<ArticleJournalistsDTO> {
    return this.httpClient.get<ArticleJournalistsDTO>(this.articleJournalistUrl);
  }

  saveArticleJournalist(articleJournalist: ArticleJournalistPrimaryKey): Observable<ArticleJournalist> {
    return this.httpClient.post<ArticleJournalist>(this.articleJournalistUrl, articleJournalist);
  }

  deleteArticleJournalist(articleId: number, journalistId: number): Observable<any> {
    const url = `${this.articleJournalistUrl}/${articleId}&${journalistId}`;
    return this.httpClient.delete(url);
  }

  getJournalistWithMostArticles(): Observable<Journalist> {
    const url = `${this.articleJournalistUrl}/most`;
    return this.httpClient.get<Journalist>(url);
  }
}
