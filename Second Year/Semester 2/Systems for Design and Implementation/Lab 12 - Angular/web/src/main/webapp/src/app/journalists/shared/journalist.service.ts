import { Injectable } from '@angular/core';
import { HttpClient } from "@angular/common/http";
import { Observable } from 'rxjs';
import { Journalist, JournalistsDTO } from './journalist.model';
import { map } from "rxjs/operators";

@Injectable({
  providedIn: 'root'
})
export class JournalistService {
  private journalistsUrl = 'http://localhost:8080/api/journalists';

  constructor(private httpClient: HttpClient) { }

  getJournalists(): Observable<JournalistsDTO> {
    return this.httpClient.get<JournalistsDTO>(this.journalistsUrl);
  }

  saveJournalist(journalist: Journalist): Observable<Journalist> {
    return this.httpClient.post<Journalist>(this.journalistsUrl, journalist);
  }

  deleteJournalist(journalistId: number): Observable<any> {
    const url = `${this.journalistsUrl}/${journalistId}`;
    return this.httpClient.delete(url);
  }

  updateJournalist(journalist: Journalist): Observable<Journalist> {
    const url = `${this.journalistsUrl}/${journalist.id}`;
    return this.httpClient.put<Journalist>(url, journalist);
  }
  
  getJournalist(id: number): Observable<any> {
    return this.getJournalists().pipe(
      map(response => {
        let journalist;
        response.journalists.forEach((elem: Journalist) => {
          if (elem.id === id) {
            journalist = elem;
          }
        })
        return journalist;
      })
    );
  }

  getJournalistsFilteredByDob(dob: string): Observable<JournalistsDTO> {
    const url = `${this.journalistsUrl}/filter/${dob}`;
    return this.httpClient.get<JournalistsDTO>(url);
  }
}
