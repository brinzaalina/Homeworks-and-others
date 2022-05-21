import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { ArticleJournalistPrimaryKey } from '../shared/article-journalist-key.model';
import { ArticleJournalist } from '../shared/article-journalist.model';
import { ArticleJournalistService } from '../shared/article-journalist.service';

@Component({
  selector: 'app-article-journalist-add',
  templateUrl: './article-journalist-add.component.html',
  styleUrls: ['./article-journalist-add.component.css']
})
export class ArticleJournalistAddComponent implements OnInit {

  constructor(private articleJournalistService: ArticleJournalistService, private router: Router) { }

  ngOnInit(): void {
  }

  saveArticleJournalist(articleId: string, journalistId: string) {
    this.articleJournalistService.saveArticleJournalist(new ArticleJournalistPrimaryKey(parseInt(articleId), parseInt(journalistId))).subscribe(_ => this.router.navigate(['/article-journalists']));
  }

  onCancel(): void {
    if(confirm("Are you sure you want to cancel?")) {
      this.router.navigate(['/article-journalists']);
    }
  }

}
