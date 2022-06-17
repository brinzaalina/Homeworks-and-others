import { Component, Input, OnInit } from '@angular/core';
import { ActivatedRoute, Params, Router } from '@angular/router';
import { switchMap } from 'rxjs';
import { Category } from 'src/app/categories/shared/category.model';
import { CategoryService } from 'src/app/categories/shared/category.service';
import { Article } from '../shared/article.model';
import { ArticleService } from '../shared/article.service';

@Component({
  selector: 'app-article-update',
  templateUrl: './article-update.component.html',
  styleUrls: ['./article-update.component.css']
})
export class ArticleUpdateComponent implements OnInit {
  @Input() article: Article = new Article();
  categories: Array<Category> = [];
  selectedCategory: number = 0;

  constructor(private articleService: ArticleService, private categoryService: CategoryService, private router: Router, private route: ActivatedRoute) { }

  ngOnInit(): void {
    this.route.params
        .pipe(switchMap((params: Params) => this.articleService.getArticle(+params['id'])))
        .subscribe(article =>  this.article = article);
    this.categoryService.getCategories().subscribe(categories => this.categories = categories.categories);
  }

  saveArticleUpdates() {
    console.log(this.article);
    this.articleService.updateArticle(this.article).subscribe(_ => this.router.navigate(['/articles']));
  }

  onCancel(): void {
    if(confirm("Are you sure you want to cancel?")) {
      this.router.navigate(['/articles']);
    }
  }

  onSelect(event: any) {
    this.selectedCategory = event.target.value;
    this.article.category = this.categories.filter(cat => cat.id == this.selectedCategory)[0];
  }
}
