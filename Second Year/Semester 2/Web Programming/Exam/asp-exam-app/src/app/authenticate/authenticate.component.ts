import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { ExamService } from '../services/exam.service';

@Component({
  selector: 'app-authenticate',
  templateUrl: './authenticate.component.html',
  styleUrls: ['./authenticate.component.css']
})
export class AuthenticateComponent implements OnInit {

  constructor(private service: ExamService, private router: Router) { }

  ngOnInit(): void {
  }

  login(usernameInput: string): void {
    if (usernameInput.trim().length > 0) {
      // sessionStorage.setItem("user", usernameInput);
      this.service.authenticate(usernameInput).subscribe(data => {
        if (data == null) {
          alert("No player found!");
        } else {
          sessionStorage.setItem("user", data.name);
          sessionStorage.setItem("position", data.position);
          this.router.navigate(['/main']);
        }
      })
    } else {
      alert("Username is empty!");
    }
  }

}
