import { HttpClient, HttpHeaders } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { catchError, Observable, of } from 'rxjs';
import { LogPost } from '../models/log-post.model';
import { Log } from '../models/log.model';

@Injectable({
  providedIn: 'root'
})
export class LogsService {
  private getAllLogsURL = 'https://localhost:44352/Main/GetAllLogs';
  private getAllLogsUserURL = 'https://localhost:44352/Main/GetLogsByUser';
  private getLogsPaginatedURL = 'https://localhost:44352/Main/GetLogsPaginated';
  private getLogsPaginatedForUserURL = 'https://localhost:44352/Main/GetLogsPaginatedForUser';
  private addLogURL = 'https://localhost:44352/Main/AddLog';
  private deleteLogURL = 'https://localhost:44352/Main/RemoveLog';
  private getFilteredLogsURL = 'https://localhost:44352/Main/GetFilteredLogs';
  httpOptions = {
    headers: new HttpHeaders({
      'Content-Type': 'application/json',
      
    })
  };
  constructor(private http: HttpClient) { }

  getAllLogs(): Observable<Log[]> {
    return this.http.get<Log[]>(this.getAllLogsURL + `?token=${localStorage.getItem("token")}`);
  }

  getAllLogsForUser(): Observable<Log[]> {
    return this.http.get<Log[]>(this.getAllLogsUserURL + `?token=${localStorage.getItem("token")}`);
  }

  getLogsPaginated(pageSize: number, page: number): Observable<Log[]> {
    return this.http.get<Log[]>(this.getLogsPaginatedURL +
      `?token=${localStorage.getItem("token")}&pageSize=${pageSize}&pageNumber=${page}`);
  }

  getLogsPaginatedForUser(pageSize: number, page: number): Observable<Log[]> {
    return this.http.get<Log[]>(this.getLogsPaginatedForUserURL +
      `?token=${localStorage.getItem("token")}&pageSize=${pageSize}&pageNumber=${page}`);
  }

  filterLogs(type: string, severity: string): Observable<Log[]> {
    return this.http.get<Log[]>(this.getFilteredLogsURL + `?token=${localStorage.getItem("token")}&type=${type}&severity=${severity}`);
  }

  addLog(type: string, severity: string, date: string, message: string) {
    // return this.http.get(this.addLogURL + `?token=${localStorage.getItem("token")}&type=${type}&severity=${severity}&date=${date}&logtext=${message}`,
    //   )
    //   .pipe(catchError(this.handleError<string>('addLog', '')));
    return this.http.post(this.addLogURL + `?token=${localStorage.getItem("token")}`, new LogPost(type, severity, date, message)).pipe(catchError(this.handleError<string>('addLog', '')));
  }

  deleteLog(logId: string) {
    return this.http.delete(this.deleteLogURL + `?token=${localStorage.getItem("token")}&id=${logId}`)
      .pipe(catchError(this.handleError<string>('deleteLog', '')));
  }
  
  private handleError<T>(operation = 'operation', result?: T) {
    return (error: any): Observable<T> => {
      alert(error.error);
      return of(result as T);
    };
  }
}
