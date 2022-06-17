import { ComponentFixture, TestBed } from '@angular/core/testing';

import { ReaderAddComponent } from './reader-add.component';

describe('ReaderAddComponent', () => {
  let component: ReaderAddComponent;
  let fixture: ComponentFixture<ReaderAddComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ ReaderAddComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(ReaderAddComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
