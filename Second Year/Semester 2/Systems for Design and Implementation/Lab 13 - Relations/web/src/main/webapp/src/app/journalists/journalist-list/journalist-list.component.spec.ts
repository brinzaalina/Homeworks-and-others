import { ComponentFixture, TestBed } from '@angular/core/testing';

import { JournalistListComponent } from './journalist-list.component';

describe('JournalistListComponent', () => {
  let component: JournalistListComponent;
  let fixture: ComponentFixture<JournalistListComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ JournalistListComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(JournalistListComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
