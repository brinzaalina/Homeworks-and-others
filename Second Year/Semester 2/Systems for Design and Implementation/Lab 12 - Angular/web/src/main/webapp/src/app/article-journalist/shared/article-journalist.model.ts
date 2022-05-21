export class ArticleJournalist {
    id: {articleid: number, journalistid: number};

    constructor(id: {articleid: number, journalistid: number}) {
        this.id = id;
    }


}

export class ArticleJournalistsDTO {
    articleJournalists: Array<ArticleJournalist>;

    constructor(articleJournalists: Array<ArticleJournalist> = []) {
        this.articleJournalists = articleJournalists;
    }
}