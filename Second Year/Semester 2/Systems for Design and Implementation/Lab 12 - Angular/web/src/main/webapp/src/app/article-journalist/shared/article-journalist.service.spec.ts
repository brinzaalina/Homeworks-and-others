import { TestBed } from '@angular/core/testing';

import { ArticleJournalistService } from './article-journalist.service';

describe('ArticleJournalistService', () => {
  let service: ArticleJournalistService;

  beforeEach(() => {
    TestBed.configureTestingModule({});
    service = TestBed.inject(ArticleJournalistService);
  });

  it('should be created', () => {
    expect(service).toBeTruthy();
  });
});
