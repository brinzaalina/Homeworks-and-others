import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Observable } from 'rxjs';
import { CategoriesDTO, Category } from './category.model';
import { map } from "rxjs/operators";

@Injectable({
  providedIn: 'root'
})
export class CategoryService {
  private categoriesUrl = 'http://localhost:8080/api/categories';

  constructor(private httpClient: HttpClient) { }

  getCategories(): Observable<CategoriesDTO> {
    return this.httpClient.get<CategoriesDTO>(this.categoriesUrl);
  }

  saveCategory(category: Category): Observable<Category> {
    return this.httpClient.post<Category>(this.categoriesUrl, category);
  }

  deleteCategory(categoryId: number): Observable<any> {
    const url = `${this.categoriesUrl}/${categoryId}`;
    return this.httpClient.delete(url);
  }

  updateCategory(category: Category): Observable<Category> {
    const url = `${this.categoriesUrl}/${category.id}`;
    return this.httpClient.put<Category>(url, category);
  }

  getCategory(id: number): Observable<any> {
    return this.getCategories().pipe(
      map(response => {
        let category;
        response.categories.forEach((elem: Category) => {
          if (elem.id === id) {
            category = elem;
          }
        })
        return category;
      })
    );
  }

  getSorted(): Observable<CategoriesDTO> {
    const url = `${this.categoriesUrl}/sort/name`;
    return this.httpClient.get<CategoriesDTO>(url);
  }
}
