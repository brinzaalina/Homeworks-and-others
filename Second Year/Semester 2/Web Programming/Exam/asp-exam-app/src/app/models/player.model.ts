export class Player {
    id!: number;
    name!: string;
    position!: string;

    constructor(name: string, id: number = 0, position: string = "") {
        this.id = id;
        this.name = name;
        this.position = position;
    }
}