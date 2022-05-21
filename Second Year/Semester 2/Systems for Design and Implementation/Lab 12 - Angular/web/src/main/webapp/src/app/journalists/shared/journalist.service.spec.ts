import { TestBed } from '@angular/core/testing';

import { JournalistService } from './journalist.service';

describe('JournalistService', () => {
  let service: JournalistService;

  beforeEach(() => {
    TestBed.configureTestingModule({});
    service = TestBed.inject(JournalistService);
  });

  it('should be created', () => {
    expect(service).toBeTruthy();
  });
});
