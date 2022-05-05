import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { LoginService } from 'src/app/services/login.service';

@Component({
  selector: 'app-login-page',
  templateUrl: './login-page.component.html',
  styleUrls: ['./login-page.component.css']
})
export class LoginPageComponent implements OnInit {
  username="";
  constructor(private loginService: LoginService, private router: Router) { }

  ngOnInit(): void {
  }

  login(usernameInput: string): void {
    if (usernameInput.trim().length > 0) {
      this.loginService.login(usernameInput).subscribe(username => {
        this.username = username;
        this.continueLogin(usernameInput);}
        // {
        // if(username === "")
        //   alert("User does not exist!");
        // localStorage.setItem("username", username);
        // }
      );
    } else {
      alert("Username is emtpy!");
    }
  }

  continueLogin(user: string): void {
    if(this.username === "")
          alert("User does not exist!");
    localStorage.setItem("username", this.username);
    console.log("User: " + localStorage.getItem("username"));
    if (localStorage.getItem('username') === user) {
      this.username = user;
      this.router.navigate(['/homepage']);
    }
  }

}
