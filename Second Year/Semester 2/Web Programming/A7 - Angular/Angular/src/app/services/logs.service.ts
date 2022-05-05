import { HttpClient, HttpHeaders } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { catchError, Observable, of } from 'rxjs';

@Injectable({
  providedIn: 'root'
})
export class LogsService {
  private getAllLogsURL = 'http://localhost/wp-lab-7/PHP/getAllLogs.php';
  private getAllLogsUserURL = 'http://localhost/wp-lab-7/PHP/getAllLogsUser.php';
  private getLogsPaginatedURL = 'http://localhost/wp-lab-7/PHP/getAllLogsPaginated.php';
  private getLogsPaginatedForUserURL = 'http://localhost/wp-lab-7/PHP/getAllLogsPaginatedForUser.php';
  private addLogURL = 'http://localhost/wp-lab-7/PHP/addLog.php';
  private deleteLogURL = 'http://localhost/wp-lab-7/PHP/deleteLog.php';
  private getFilteredLogsURL = 'http://localhost/wp-lab-7/PHP/getLogsByTypeAndSeverity.php';
  httpOptions = {
    headers: new HttpHeaders({
      'Content-Type': 'application/json'
    })
  };
  constructor(private http: HttpClient) { }

  getAllLogs(): Observable<Array<string[]>> {
    return this.http.get<Array<string[]>>(this.getAllLogsURL);
  }

  getAllLogsForUser(): Observable<Array<string[]>> {
    return this.http.get<Array<string[]>>(this.getAllLogsUserURL + `?user=${localStorage.getItem('username')}`);
  }

  getLogsPaginated(pageSize: number, page: number): Observable<Array<string[]>> {
    return this.http.get<Array<string[]>>(this.getLogsPaginatedURL +
      `?pageSize=${pageSize}&page=${page}`);
  }

  getLogsPaginatedForUser(pageSize: number, page: number): Observable<Array<string[]>> {
    return this.http.get<Array<string[]>>(this.getLogsPaginatedForUserURL +
      `?pageSize=${pageSize}&page=${page}` + `&user=${localStorage.getItem('username')}`);
  }

  filterLogs(type: string, severity: string): Observable<Array<string[]>> {
    return this.http.get<Array<string[]>>(this.getFilteredLogsURL + `?type=${type}` + `&severity=${severity}`);
  }

  addLog(type: string, severity: string, date: string, message: string): Observable<string> {
    return this.http.get(this.addLogURL + `?type=${type}` + `&severity=${severity}` +
      `&date=${date}` + `&user=${localStorage.getItem('username')}` + `&message=${message}`,
      {responseType: 'text'})
      .pipe(catchError(this.handleError<string>('addLog', '')));
  }

  deleteLog(logId: string): Observable<string> {
    return this.http.get(this.deleteLogURL + `?logId=${logId}` + `&user=${localStorage.getItem('username')}`,
      {responseType: 'text'})
      .pipe(catchError(this.handleError<string>('deleteLog', '')));
  }
  
  private handleError<T>(operation = 'operation', result?: T) {
    return (error: any): Observable<T> => {
      console.error(error);
      return of(result as T);
    };
  }
}
