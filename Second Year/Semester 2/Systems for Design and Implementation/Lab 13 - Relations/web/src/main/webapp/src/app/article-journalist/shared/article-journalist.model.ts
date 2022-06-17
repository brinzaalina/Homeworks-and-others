import { Article } from "src/app/articles/shared/article.model";
import { Journalist } from "src/app/journalists/shared/journalist.model";

export class ArticleJournalist {
    article: Article;
    journalist: Journalist;

    constructor(article: Article = new Article(), journalist: Journalist = new Journalist()) {
        this.article = article;
        this.journalist = journalist;
    }


}

export class ArticleJournalistsDTO {
    articleJournalists: Array<ArticleJournalist>;

    constructor(articleJournalists: Array<ArticleJournalist> = []) {
        this.articleJournalists = articleJournalists;
    }
}