import { Component, NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { ArticleJournalistAddComponent } from './article-journalist/article-journalist-add/article-journalist-add.component';
import { ArticleJournalistComponent } from './article-journalist/article-journalist.component';
import { ArticleAddComponent } from './articles/article-add/article-add.component';
import { ArticleUpdateComponent } from './articles/article-update/article-update.component';
import { ArticlesComponent } from './articles/articles.component';
import { CategoriesComponent } from './categories/categories.component';
import { CategoryAddComponent } from './categories/category-add/category-add.component';
import { CategoryUpdateComponent } from './categories/category-update/category-update.component';
import { HomepageComponent } from './homepage/homepage.component';
import { JournalistAddComponent } from './journalists/journalist-add/journalist-add.component';
import { JournalistUpdateComponent } from './journalists/journalist-update/journalist-update.component';
import { JournalistsComponent } from './journalists/journalists.component';
import { ReaderAddComponent } from './reader/reader-add/reader-add.component';
import { ReaderUpdateComponent } from './reader/reader-update/reader-update.component';
import { ReaderComponent } from './reader/reader.component';

const routes: Routes = [
  {path: '', component: HomepageComponent},
  {path: 'journalists', component: JournalistsComponent},
  {path: 'journalist-add', component: JournalistAddComponent},
  {path: 'journalist-update/:id', component: JournalistUpdateComponent},
  {path: 'categories', component: CategoriesComponent},
  {path: 'category-add', component: CategoryAddComponent},
  {path: 'category-update/:id', component: CategoryUpdateComponent},
  {path: 'articles', component: ArticlesComponent},
  {path: 'article-add', component: ArticleAddComponent},
  {path: 'article-update/:id', component: ArticleUpdateComponent},
  {path: 'article-journalists', component: ArticleJournalistComponent},
  {path: 'article-journalist-add', component: ArticleJournalistAddComponent},
  {path: 'readers', component: ReaderComponent},
  {path: 'reader-add', component: ReaderAddComponent},
  {path: 'reader-update/:id', component: ReaderUpdateComponent}
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
