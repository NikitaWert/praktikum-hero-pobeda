import { ComponentFixture, TestBed } from '@angular/core/testing';

import { ChartMoneyByPeriodComponent } from './chart-money-by-period.component';

describe('ChartMoneyByPeriodComponent', () => {
  let component: ChartMoneyByPeriodComponent;
  let fixture: ComponentFixture<ChartMoneyByPeriodComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ ChartMoneyByPeriodComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(ChartMoneyByPeriodComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
