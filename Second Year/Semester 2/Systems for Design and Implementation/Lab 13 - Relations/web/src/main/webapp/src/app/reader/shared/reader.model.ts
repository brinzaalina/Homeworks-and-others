import { Contact } from "./contact.model";

export class Reader {
    id: number;
    lastName: string;
    firstName: string;
    contact: Contact;

    constructor(id: number = 0, lastName = "", firstName = "", contact = new Contact()) {
        this.id = id;
        this.lastName = lastName;
        this.firstName = firstName;
        this.contact = contact;
    }
}

export class ReadersDTO {
    readers: Array<Reader>;

    constructor(readers: Array<Reader> = []) {
        this.readers = readers;
    }
}