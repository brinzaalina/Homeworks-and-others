import { ComponentFixture, TestBed } from '@angular/core/testing';

import { ReaderUpdateComponent } from './reader-update.component';

describe('ReaderUpdateComponent', () => {
  let component: ReaderUpdateComponent;
  let fixture: ComponentFixture<ReaderUpdateComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ ReaderUpdateComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(ReaderUpdateComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
