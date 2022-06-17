import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { Contact } from '../shared/contact.model';
import { Reader } from '../shared/reader.model';
import { ReaderService } from '../shared/reader.service';

@Component({
  selector: 'app-reader-add',
  templateUrl: './reader-add.component.html',
  styleUrls: ['./reader-add.component.css']
})
export class ReaderAddComponent implements OnInit {

  constructor(private service: ReaderService, private router: Router) { }

  ngOnInit(): void {
  }

  saveReader(lastName: string, firstName: string, email: string, phone: string, address: string) {
    this.service.saveReader(new Reader(0, lastName, firstName,new Contact(email, phone, address))).subscribe(_ => this.router.navigate(['/readers']));
  }

  onCancel(): void {
    if(confirm("Are you sure you want to cancel?")) {
      this.router.navigate(['/readers']);
    }
  }

}
