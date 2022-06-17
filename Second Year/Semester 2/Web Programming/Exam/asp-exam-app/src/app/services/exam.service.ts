import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Observable } from 'rxjs';
import { Player } from '../models/player.model';

@Injectable({
  providedIn: 'root'
})
export class ExamService {
  private authUrl = 'https://localhost:7250/Exam/auth';
  private url = 'https://localhost:7250/Exam';

  constructor(private http: HttpClient) { }

  authenticate(username: string): Observable<Player> {
    return this.http.post<Player>(this.authUrl, new Player(username));
  }

  getPlayersWithMatchingName(name: string): Observable<Array<Player>> {
    return this.http.get<Array<Player>>(`${this.url}/playersWithName?name=${name}`);
  }

  getFirstDegree(name: string): Observable<Array<Player>> {
    return this.http.get<Array<Player>>(`${this.url}/players1?name=${name}`);
  }

  getSecondDegree(name: string): Observable<Array<Player>> {
    return this.http.get<Array<Player>>(`${this.url}/players2?name=${name}`);
  }

  getThirdDegree(name: string): Observable<Array<Player>> {
    return this.http.get<Array<Player>>(`${this.url}/players3?name=${name}`);
  }
}
