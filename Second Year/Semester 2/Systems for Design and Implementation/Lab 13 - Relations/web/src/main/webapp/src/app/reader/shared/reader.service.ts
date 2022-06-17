import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { map, Observable } from 'rxjs';
import { Reader, ReadersDTO } from './reader.model';

@Injectable({
  providedIn: 'root'
})
export class ReaderService {

  private readersUrl = 'http://localhost:8080/api/readers';

  constructor(private httpClient: HttpClient) { }

  getReaders(): Observable<ReadersDTO> {
    return this.httpClient.get<ReadersDTO>(this.readersUrl);
  }

  saveReader(reader: Reader): Observable<Reader> {
    return this.httpClient.post<Reader>(this.readersUrl, reader);
  }

  deleteReader(readerId: number): Observable<any> {
    const url = `${this.readersUrl}/${readerId}`;
    return this.httpClient.delete(url);
  }

  updateReader(reader: Reader): Observable<Reader> {
    const url = `${this.readersUrl}/${reader.id}`;
    return this.httpClient.put<Reader>(url, reader);
  }

  getReader(id: number): Observable<any> {
    return this.getReaders().pipe(
      map(response => {
        let reader;
        response.readers.forEach((elem: Reader) => {
          if (elem.id === id) {
            reader = elem;
          }
        })
        return reader;
      })
    );
  }
}
