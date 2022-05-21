import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { Journalist } from 'src/app/journalists/shared/journalist.model';
import { ArticleJournalist } from '../shared/article-journalist.model';
import { ArticleJournalistService } from '../shared/article-journalist.service';

@Component({
  selector: 'app-article-journalist-list',
  templateUrl: './article-journalist-list.component.html',
  styleUrls: ['./article-journalist-list.component.css']
})
export class ArticleJournalistListComponent implements OnInit {
  articleJournalists: Array<ArticleJournalist> = [];
  bestJournalist: Journalist = new Journalist();

  constructor(private articleJournalistService: ArticleJournalistService, private router: Router) { }

  ngOnInit(): void {
    this.articleJournalistService.getArticleJournalists().subscribe(
      articleJournalists => this.articleJournalists = articleJournalists.articleJournalists
    );
    this.articleJournalistService.getJournalistWithMostArticles().subscribe(
      journalist => this.bestJournalist = journalist
    )
  }

  deleteArticleJournalist(articleJournalist: ArticleJournalist) {
    if(confirm("Are you sure you want to delete the selected article-journalist?")) {
      this.articleJournalistService.deleteArticleJournalist(articleJournalist.id.articleid, articleJournalist.id.journalistid).subscribe(_ => {
        this.articleJournalists = this.articleJournalists.filter(aj => { 
          return ((aj.id.articleid !== articleJournalist.id.articleid) || (aj.id.journalistid !== articleJournalist.id.journalistid))
        });
        this.ngOnInit();
      });
    }
  }

  navigateToAddArticleJournalist() {
    this.router.navigate(['/article-journalist-add']);
  }

}
