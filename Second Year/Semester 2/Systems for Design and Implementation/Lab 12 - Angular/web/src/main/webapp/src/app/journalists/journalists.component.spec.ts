import { ComponentFixture, TestBed } from '@angular/core/testing';

import { JournalistsComponent } from './journalists.component';

describe('JournalistsComponent', () => {
  let component: JournalistsComponent;
  let fixture: ComponentFixture<JournalistsComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ JournalistsComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(JournalistsComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
