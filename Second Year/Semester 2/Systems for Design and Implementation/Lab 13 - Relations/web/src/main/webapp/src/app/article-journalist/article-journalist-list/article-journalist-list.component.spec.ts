import { ComponentFixture, TestBed } from '@angular/core/testing';

import { ArticleJournalistListComponent } from './article-journalist-list.component';

describe('ArticleJournalistListComponent', () => {
  let component: ArticleJournalistListComponent;
  let fixture: ComponentFixture<ArticleJournalistListComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ ArticleJournalistListComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(ArticleJournalistListComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
