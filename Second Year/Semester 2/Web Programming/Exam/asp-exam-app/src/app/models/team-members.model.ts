export class TeamMembers {
    id!: number;
    idPlayer1!: number;
    idPlayer2!: number;
    idTeam!: number;

    constructor(id: number, idPlayer1: number, idPlayer2: number, idTeam: number) {
        this.id = id;
        this.idPlayer1 = idPlayer1;
        this.idPlayer2 = idPlayer2;
        this.idTeam = idTeam;
    }
}