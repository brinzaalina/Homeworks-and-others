import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';

import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { JournalistsComponent } from './journalists/journalists.component';
import { JournalistListComponent } from './journalists/journalist-list/journalist-list.component';
import { JournalistAddComponent } from './journalists/journalist-add/journalist-add.component';
import { JournalistUpdateComponent } from './journalists/journalist-update/journalist-update.component';
import { HomepageComponent } from './homepage/homepage.component';
import { HttpClientModule } from '@angular/common/http';
import { FormsModule } from '@angular/forms';
import { CategoriesComponent } from './categories/categories.component';
import { CategoryAddComponent } from './categories/category-add/category-add.component';
import { CategoryListComponent } from './categories/category-list/category-list.component';
import { CategoryUpdateComponent } from './categories/category-update/category-update.component';
import { ArticlesComponent } from './articles/articles.component';
import { ArticleAddComponent } from './articles/article-add/article-add.component';
import { ArticleListComponent } from './articles/article-list/article-list.component';
import { ArticleUpdateComponent } from './articles/article-update/article-update.component';
import { ArticleJournalistComponent } from './article-journalist/article-journalist.component';
import { ArticleJournalistAddComponent } from './article-journalist/article-journalist-add/article-journalist-add.component';
import { ArticleJournalistListComponent } from './article-journalist/article-journalist-list/article-journalist-list.component';
import { ReaderComponent } from './reader/reader.component';
import { ReaderAddComponent } from './reader/reader-add/reader-add.component';
import { ReaderListComponent } from './reader/reader-list/reader-list.component';
import { ReaderUpdateComponent } from './reader/reader-update/reader-update.component';

@NgModule({
  declarations: [
    AppComponent,
    JournalistsComponent,
    JournalistListComponent,
    JournalistAddComponent,
    JournalistUpdateComponent,
    HomepageComponent,
    CategoriesComponent,
    CategoryAddComponent,
    CategoryListComponent,
    CategoryUpdateComponent,
    ArticlesComponent,
    ArticleAddComponent,
    ArticleListComponent,
    ArticleUpdateComponent,
    ArticleJournalistComponent,
    ArticleJournalistAddComponent,
    ArticleJournalistListComponent,
    ReaderComponent,
    ReaderAddComponent,
    ReaderListComponent,
    ReaderUpdateComponent
  ],
  imports: [
    BrowserModule,
    AppRoutingModule,
    HttpClientModule,
    FormsModule
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
