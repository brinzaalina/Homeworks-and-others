export class Journalist {
    id: number;
    lastName: string;
    firstName: string;
    email: string;
    dob: Date;

    constructor(id: number = 0, lastName = "", firstName = "", email = "", dob = new Date()) {
        this.id = id;
        this.lastName = lastName;
        this.firstName = firstName;
        this.email = email;
        this.dob = dob;
    }
}

export class JournalistsDTO {
    journalists: Array<Journalist>;

    constructor(journalists: Array<Journalist> = []) {
        this.journalists = journalists;
    }
}