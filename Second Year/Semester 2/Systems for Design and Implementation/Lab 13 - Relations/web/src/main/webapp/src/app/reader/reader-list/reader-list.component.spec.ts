import { ComponentFixture, TestBed } from '@angular/core/testing';

import { ReaderListComponent } from './reader-list.component';

describe('ReaderListComponent', () => {
  let component: ReaderListComponent;
  let fixture: ComponentFixture<ReaderListComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ ReaderListComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(ReaderListComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
