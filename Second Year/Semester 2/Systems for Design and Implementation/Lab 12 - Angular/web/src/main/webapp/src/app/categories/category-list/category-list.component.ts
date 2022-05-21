import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { Category } from '../shared/category.model';
import { CategoryService } from '../shared/category.service';

@Component({
  selector: 'app-category-list',
  templateUrl: './category-list.component.html',
  styleUrls: ['./category-list.component.css']
})
export class CategoryListComponent implements OnInit {
  categories: Array<Category> = [];

  constructor(private categoryService: CategoryService, private router: Router) { }

  ngOnInit(): void {
    this.categoryService.getCategories().subscribe(
      categories => this.categories = categories.categories
    );
  }

  deleteCategory(category: Category) {
    if(confirm("Are you sure you want to delete the selected category?")) {
      this.categoryService.deleteCategory(category.id).subscribe(_ => this.categories = this.categories.filter(c => c.id !== category.id));
    }
  }

  updateCateogory(category: Category) {
    this.router.navigate(['/category-update', category.id]);
  }

  navigateToAddCategory() {
    this.router.navigate(["/category-add"]);
  }

  sortByName() {
    this.categoryService.getSorted().subscribe(response => {
      this.categories = response.categories;
    })
  }

}
