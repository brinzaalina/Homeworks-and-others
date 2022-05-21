import { ComponentFixture, TestBed } from '@angular/core/testing';

import { ArticleJournalistComponent } from './article-journalist.component';

describe('ArticleJournalistComponent', () => {
  let component: ArticleJournalistComponent;
  let fixture: ComponentFixture<ArticleJournalistComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ ArticleJournalistComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(ArticleJournalistComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
