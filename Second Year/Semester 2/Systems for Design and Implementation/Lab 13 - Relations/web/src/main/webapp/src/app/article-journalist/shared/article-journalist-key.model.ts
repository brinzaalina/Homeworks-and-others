export class ArticleJournalistPrimaryKey {
    articleId: number;
    journalistId: number;

    constructor(articleid = 0, journalistid = 0) {
        this.articleId = articleid;
        this.journalistId = journalistid;
    }
}