import { ComponentFixture, TestBed } from '@angular/core/testing';

import { CircleDiagrammComponent } from './circle-diagramm.component';

describe('CircleDiagrammComponent', () => {
  let component: CircleDiagrammComponent;
  let fixture: ComponentFixture<CircleDiagrammComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ CircleDiagrammComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(CircleDiagrammComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
