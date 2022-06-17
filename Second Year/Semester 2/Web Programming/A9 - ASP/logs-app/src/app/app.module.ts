import { HttpClientModule } from '@angular/common/http';
import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';

import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { AddPageComponent } from './pages/add-page/add-page.component';
import { ErrorPageComponent } from './pages/error-page/error-page.component';
import { HomePageComponent } from './pages/home-page/home-page.component';
import { LoginPageComponent } from './pages/login-page/login-page.component';
import { RemovePageComponent } from './pages/remove-page/remove-page.component';
import { ShowPageComponent } from './pages/show-page/show-page.component';

@NgModule({
  declarations: [
    AppComponent,
    AddPageComponent,
    ErrorPageComponent,
    HomePageComponent,
    LoginPageComponent,
    RemovePageComponent,
    ShowPageComponent
  ],
  imports: [
    BrowserModule,
    AppRoutingModule,
    HttpClientModule
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
