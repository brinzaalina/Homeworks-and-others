import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { Category } from 'src/app/categories/shared/category.model';
import { CategoryService } from 'src/app/categories/shared/category.service';
import { Article } from '../shared/article.model';
import { ArticleService } from '../shared/article.service';

@Component({
  selector: 'app-article-add',
  templateUrl: './article-add.component.html',
  styleUrls: ['./article-add.component.css']
})
export class ArticleAddComponent implements OnInit {
  categories: Array<Category> = [];
  selectedCategory: number = 0;

  constructor(private articleService: ArticleService, private categoryService: CategoryService,private router: Router) { }

  ngOnInit(): void {
    this.categoryService.getCategories().subscribe(
      categories => {
        this.categories = categories.categories;
        this.selectedCategory = categories.categories[0].id;
      }
    )
  }

  saveArticle(title: string, text: string) {
    this.articleService.saveArticle(new Article(this.categories.filter(cat => cat.id == this.selectedCategory)[0],0, title, text)).subscribe(_ => this.router.navigate(['/articles']));
  }

  onCancel(): void {
    if(confirm("Are you sure you want to cancel?")) {
      this.router.navigate(['/articles']);
    }
  }

  onSelect(event: any) {
    this.selectedCategory = event.target.value;
    console.log(this.selectedCategory);
  }
}
