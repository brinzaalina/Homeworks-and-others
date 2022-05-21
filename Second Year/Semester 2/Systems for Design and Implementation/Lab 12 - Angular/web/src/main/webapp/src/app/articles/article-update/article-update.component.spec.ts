import { ComponentFixture, TestBed } from '@angular/core/testing';

import { ArticleUpdateComponent } from './article-update.component';

describe('ArticleUpdateComponent', () => {
  let component: ArticleUpdateComponent;
  let fixture: ComponentFixture<ArticleUpdateComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ ArticleUpdateComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(ArticleUpdateComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
