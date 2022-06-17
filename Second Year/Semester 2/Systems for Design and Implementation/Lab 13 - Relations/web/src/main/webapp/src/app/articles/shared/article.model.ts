import { Category } from "src/app/categories/shared/category.model";

export class Article {
    id: number;
    title: string;
    text: string;
    category: Category;

    constructor(category: Category = new Category(), id: number = 0, title = "", text = "") {
        this.id = id;
        this.title = title;
        this.text = text;
        this.category = category;
    }
}

export class ArticlesDTO {
    articles: Array<Article>;

    constructor(articles: Array<Article> = []) {
        this.articles = articles;
    }
}