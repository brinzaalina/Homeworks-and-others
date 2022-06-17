import { Component, Input, OnInit } from '@angular/core';
import { ActivatedRoute, Params, Router } from '@angular/router';
import { switchMap } from 'rxjs';
import { Reader } from '../shared/reader.model';
import { ReaderService } from '../shared/reader.service';

@Component({
  selector: 'app-reader-update',
  templateUrl: './reader-update.component.html',
  styleUrls: ['./reader-update.component.css']
})
export class ReaderUpdateComponent implements OnInit {

  @Input() reader: Reader = new Reader();
  constructor(private service: ReaderService, private router: Router, private route: ActivatedRoute) { }

  ngOnInit(): void {
    this.route.params
        .pipe(switchMap((params: Params) => this.service.getReader(+params['id'])))
        .subscribe(reader =>  {this.reader = reader});
  }

  saveReaderUpdates() {
    this.service.updateReader(this.reader).subscribe(_ => this.router.navigate(['/readers']));
  }

  onCancel(): void {
    if(confirm("Are you sure you want to cancel?")) {
      this.router.navigate(['/readers']);
    }
  }
}
