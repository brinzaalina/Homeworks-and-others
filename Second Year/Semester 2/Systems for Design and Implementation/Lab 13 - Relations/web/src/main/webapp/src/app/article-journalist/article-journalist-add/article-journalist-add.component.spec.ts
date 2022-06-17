import { ComponentFixture, TestBed } from '@angular/core/testing';

import { ArticleJournalistAddComponent } from './article-journalist-add.component';

describe('ArticleJournalistAddComponent', () => {
  let component: ArticleJournalistAddComponent;
  let fixture: ComponentFixture<ArticleJournalistAddComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ ArticleJournalistAddComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(ArticleJournalistAddComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
