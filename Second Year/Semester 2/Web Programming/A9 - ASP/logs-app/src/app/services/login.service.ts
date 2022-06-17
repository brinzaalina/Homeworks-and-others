import { Injectable } from '@angular/core';
import { HttpClient, HttpHeaders } from '@angular/common/http';
import { catchError, Observable, of } from 'rxjs';
import { Token } from '../models/token.model';

@Injectable({
  providedIn: 'root'
})
export class LoginService {
  private URL = 'https://localhost:44352/Main';
  username = "";
  httpOptions = {
    headers: new HttpHeaders({
      'Content-Type': 'application/json'
    })
  };

  constructor(private http: HttpClient) { }

  login(usernameInput: string, password: string): Observable<Token> {
    return this.http.get<Token>(`${this.URL}/Login?username=${usernameInput}&password=${password}`);
  }

  logout() {
    return this.http.get(this.URL + "/Logout", {responseType: 'text', withCredentials: true});
  }

  private handleError<T>(operation = 'operation', result?: T) {
    return (error: any): Observable<T> => {
      console.log(error);
      return of(result as T);
    }
  }
}
