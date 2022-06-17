import { Token } from '@angular/compiler';
import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { LoginService } from 'src/app/services/login.service';
import {CookieService} from "ngx-cookie-service";

@Component({
  selector: 'app-login-page',
  templateUrl: './login-page.component.html',
  styleUrls: ['./login-page.component.css']
})
export class LoginPageComponent implements OnInit {
  constructor(private loginService: LoginService, private router: Router, private cookieService: CookieService) { }

  ngOnInit(): void {
  }

  login(usernameInput: string, passwordInput: string): void {
    if (usernameInput.trim().length > 0 && passwordInput.trim().length > 0) {
      this.loginService.login(usernameInput, passwordInput).subscribe(u => {
        if (u != null) {
          localStorage.setItem("token", u.token);
          this.cookieService.set("loggedIn", "1");
          this.router.navigate(['/homepage']);
        } else alert("Invalid credentials!");
      }
      );
    } else {
      alert("Username/pasword is empty!");
    }
  }

}
