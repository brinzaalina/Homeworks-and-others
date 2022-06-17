export class Contact {
    email: string;
    phone: string;
    address: string;

    constructor(email = "", phone = "", address = "") {
        this.email = email;
        this.phone = phone;
        this.address = address;
    }
}