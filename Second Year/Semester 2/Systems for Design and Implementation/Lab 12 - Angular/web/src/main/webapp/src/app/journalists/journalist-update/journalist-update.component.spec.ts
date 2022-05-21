import { ComponentFixture, TestBed } from '@angular/core/testing';

import { JournalistUpdateComponent } from './journalist-update.component';

describe('JournalistUpdateComponent', () => {
  let component: JournalistUpdateComponent;
  let fixture: ComponentFixture<JournalistUpdateComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ JournalistUpdateComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(JournalistUpdateComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
