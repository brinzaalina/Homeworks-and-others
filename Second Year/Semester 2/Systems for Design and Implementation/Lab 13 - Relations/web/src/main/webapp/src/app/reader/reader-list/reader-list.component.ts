import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { Reader } from '../shared/reader.model';
import { ReaderService } from '../shared/reader.service';

@Component({
  selector: 'app-reader-list',
  templateUrl: './reader-list.component.html',
  styleUrls: ['./reader-list.component.css']
})
export class ReaderListComponent implements OnInit {

  readers: Array<Reader> = [];

  constructor(private readerService: ReaderService, private router: Router) { }

  ngOnInit(): void {
    this.readerService.getReaders().subscribe(
      readers => {this.readers = readers.readers; console.log(readers)}
    );
  }

  deleteReader(reader: Reader) {
    if(confirm("Are you sure you want to delete the selected reader?")) {
      this.readerService.deleteReader(reader.id).subscribe(_ => this.readers = this.readers.filter(r => r.id !== reader.id));
    }
  }

  updateReader(reader: Reader) {
    this.router.navigate(['/reader-update', reader.id]);
  }

  navigateToAddReader() {
    this.router.navigate(["/reader-add"]);
  }
}
