import { DatePipe, formatDate } from '@angular/common';
import { Component, OnInit } from '@angular/core';
import { DateAdapter } from '@angular/material/core';
import { Observable } from 'rxjs';
import { MoneyChartService } from './money-chart.service';
import localeRu from '@angular/common/locales/ru';

@Component({
	selector: 'app-chart-money-by-period',
	templateUrl: './chart-money-by-period.component.html',
	styleUrls: ['./chart-money-by-period.component.scss']
})
export class ChartMoneyByPeriodComponent implements OnInit {

	single: Observable<any[]>;
	multi: any[];

	view: any[] = [700, 400];

	showXAxis = true;
	showYAxis = true;
	gradient = false;
	showLegend = false;
	showXAxisLabel = true;
	xAxisLabel = 'Даты';
	showYAxisLabel = true;
	yAxisLabel = 'Прибыль';

	colorScheme = {
		domain: ['#8f509d']
	};

	constructor(public moneyService: MoneyChartService) {	}

	ngOnInit(): void {
		this.single = this.moneyService.setData();

	}

	onSelect(event: any): void {
		// console.log(event);
	}

	xAxisTickFormatting(e: any): string {

		return e.slice(4, 7) + e.slice(10);
	}

}
