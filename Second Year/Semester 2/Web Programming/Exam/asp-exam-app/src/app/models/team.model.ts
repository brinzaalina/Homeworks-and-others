export class Team {
    id!: number;
    name!: string;
    homeCity!: string;

    constructor(id: number, name: string, homeCity: string) {
        this.id = id;
        this.name = name;
        this.homeCity = homeCity;
    }
}