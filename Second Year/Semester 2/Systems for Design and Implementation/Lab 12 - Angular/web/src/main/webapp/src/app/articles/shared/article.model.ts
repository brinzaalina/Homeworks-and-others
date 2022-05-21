export class Article {
    id: number;
    title: string;
    text: string;
    categoryId: number;

    constructor(id: number = 0, title = "", text = "", categoryId: number = 0) {
        this.id = id;
        this.title = title;
        this.text = text;
        this.categoryId = categoryId;
    }
}

export class ArticlesDTO {
    articles: Array<Article>;

    constructor(articles: Array<Article> = []) {
        this.articles = articles;
    }
}