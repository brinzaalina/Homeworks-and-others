import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { Player } from '../models/player.model';
import { ExamService } from '../services/exam.service';

@Component({
  selector: 'app-main',
  templateUrl: './main.component.html',
  styleUrls: ['./main.component.css']
})
export class MainComponent implements OnInit {
  username: string = "";
  position: string = "";
  players: Array<Player> = [];
  searchName: string = "";
  firstDegree: Array<Player> = [];
  secondDegree: Array<Player> = [];
  thirdDegree: Array<Player> = [];

  constructor(private service: ExamService, private router: Router) { }

  ngOnInit(): void {
    var user = sessionStorage.getItem("user");
    var position = sessionStorage.getItem("position");
    if (user == null) {
      this.router.navigate(['']);
    } else {
      this.username = user;
      if (position != null) {
      this.position = position;
      }
      this.getFirstDegree();
      this.getSecondDegree();
      this.getThirdDegree();
    }
  }

  compare(name1: string, name2: string) {
    return name1 < name2;
  }

  getPlayersMatching($event: KeyboardEvent) {
    this.service.getPlayersWithMatchingName(this.searchName).subscribe(data => {
      this.players = data.sort((a, b) => a.name.localeCompare(b.name));
    })
  }

  getFirstDegree() {
    this.service.getFirstDegree(this.username).subscribe(data => this.firstDegree = data);
  }

  getSecondDegree() {
    this.service.getSecondDegree(this.username).subscribe(data => this.secondDegree = data);
  }
  
  getThirdDegree() {
    this.service.getThirdDegree(this.username).subscribe(data => this.thirdDegree = data);
  }

  filterByPosition(event: any) {
    if (event.target.checked) {
      this.firstDegree = this.firstDegree.filter(p => p.position == this.position);
      this.secondDegree = this.secondDegree.filter(p => p.position == this.position);
      this.thirdDegree = this.thirdDegree.filter(p => p.position == this.position);
    } else {
      this.getFirstDegree();
      this.getSecondDegree();
      this.getThirdDegree();
    }
  }

  logout() {
    sessionStorage.clear();
    this.router.navigate(['']);
  }

}
