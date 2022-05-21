export class Category {
    id: number;
    name: string;

    constructor(id: number = 0, name = "") {
        this.id = id;
        this.name = name;
    }
}

export class CategoriesDTO {
    categories: Array<Category>;

    constructor(categories: Array<Category> = []) {
        this.categories = categories;
    }
}