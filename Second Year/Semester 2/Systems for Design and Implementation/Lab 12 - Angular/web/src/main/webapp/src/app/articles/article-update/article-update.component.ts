import { Component, Input, OnInit } from '@angular/core';
import { ActivatedRoute, Params, Router } from '@angular/router';
import { switchMap } from 'rxjs';
import { Article } from '../shared/article.model';
import { ArticleService } from '../shared/article.service';

@Component({
  selector: 'app-article-update',
  templateUrl: './article-update.component.html',
  styleUrls: ['./article-update.component.css']
})
export class ArticleUpdateComponent implements OnInit {
  @Input() article: Article = new Article();

  constructor(private articleService: ArticleService, private router: Router, private route: ActivatedRoute) { }

  ngOnInit(): void {
    this.route.params
        .pipe(switchMap((params: Params) => this.articleService.getArticle(+params['id'])))
        .subscribe(article =>  this.article = article);
  }

  saveArticleUpdates() {
    this.articleService.updateArticle(this.article).subscribe(_ => this.router.navigate(['/articles']));
  }

  onCancel(): void {
    if(confirm("Are you sure you want to cancel?")) {
      this.router.navigate(['/articles']);
    }
  }
}
