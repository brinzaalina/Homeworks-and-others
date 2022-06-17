import { Component, Input, OnInit } from '@angular/core';
import { ActivatedRoute, Params, Router } from '@angular/router';
import { switchMap } from 'rxjs';
import { Category } from '../shared/category.model';
import { CategoryService } from '../shared/category.service';

@Component({
  selector: 'app-category-update',
  templateUrl: './category-update.component.html',
  styleUrls: ['./category-update.component.css']
})
export class CategoryUpdateComponent implements OnInit {
  @Input() category: Category = new Category();

  constructor(private service: CategoryService, private router: Router, private route: ActivatedRoute) { }

  ngOnInit(): void {
    this.route.params
        .pipe(switchMap((params: Params) => this.service.getCategory(+params['id'])))
        .subscribe(category =>  this.category = category);
  } 

  saveCategoryUpdates() {
    this.service.updateCategory(this.category).subscribe(_ => this.router.navigate(['/categories']));
  }

  onCancel(): void {
    if(confirm("Are you sure you want to cancel?")) {
      this.router.navigate(['/categories']);
    }
  }
}
