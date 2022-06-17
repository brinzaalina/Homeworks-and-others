import { ComponentFixture, TestBed } from '@angular/core/testing';

import { JournalistAddComponent } from './journalist-add.component';

describe('JournalistAddComponent', () => {
  let component: JournalistAddComponent;
  let fixture: ComponentFixture<JournalistAddComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ JournalistAddComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(JournalistAddComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
