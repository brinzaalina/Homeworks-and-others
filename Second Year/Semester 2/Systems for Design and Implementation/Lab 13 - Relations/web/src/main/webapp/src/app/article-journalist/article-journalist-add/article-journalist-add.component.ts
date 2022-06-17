import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { Article } from 'src/app/articles/shared/article.model';
import { ArticleService } from 'src/app/articles/shared/article.service';
import { Journalist } from 'src/app/journalists/shared/journalist.model';
import { JournalistService } from 'src/app/journalists/shared/journalist.service';
import { ArticleJournalistPrimaryKey } from '../shared/article-journalist-key.model';
import { ArticleJournalist } from '../shared/article-journalist.model';
import { ArticleJournalistService } from '../shared/article-journalist.service';

@Component({
  selector: 'app-article-journalist-add',
  templateUrl: './article-journalist-add.component.html',
  styleUrls: ['./article-journalist-add.component.css']
})
export class ArticleJournalistAddComponent implements OnInit {
  articles: Array<Article> = [];
  journalists: Array<Journalist> = [];
  selectedArticle: number = 0;
  selectedJournalist: number = 0;

  constructor(private articleJournalistService: ArticleJournalistService,private articleService: ArticleService, private journalistService: JournalistService, private router: Router) { }

  ngOnInit(): void {
    this.articleService.getArticles().subscribe(
      articles => {
        this.articles = articles.articles;
        this.selectedArticle = articles.articles[0].id;
      }
    );
    this.journalistService.getJournalists().subscribe(
      journalists => {
        this.journalists = journalists.journalists;
        this.selectedJournalist = journalists.journalists[0].id;
      }
    );
  }

  saveArticleJournalist() {
    this.articleJournalistService.saveArticleJournalist(new ArticleJournalistPrimaryKey(this.articles.filter(article => article.id == this.selectedArticle)[0].id, this.journalists.filter(j => j.id == this.selectedJournalist)[0].id)).subscribe(_ => this.router.navigate(['/article-journalists']));
  }

  onCancel(): void {
    if(confirm("Are you sure you want to cancel?")) {
      this.router.navigate(['/article-journalists']);
    }
  }

  onSelectArticle(event: any) {
    this.selectedArticle = event.target.value;
    console.log(this.selectedArticle);
  }

  onSelectJournalist(event: any) {
    this.selectedJournalist = event.target.value;
    console.log(this.selectedJournalist);
  }

}
