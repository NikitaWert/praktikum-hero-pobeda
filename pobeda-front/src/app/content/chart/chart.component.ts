import { Component, OnInit } from '@angular/core';
import { Observable } from 'rxjs';
import { PieChartService } from '../circle-diagramm/pie-chart.service';


@Component({
	selector: 'app-chart',
	templateUrl: './chart.component.html',
	styleUrls: ['./chart.component.scss']
})
export class ChartComponent implements OnInit {
	single: Observable<any[]>;
	multi: any[];

	view: any[] = [700, 400];

	showXAxis = true;
	showYAxis = true;
	gradient = false;
	showLegend = false;
	showXAxisLabel = true;
	xAxisLabel = 'Приюты';
	showYAxisLabel = true;
	yAxisLabel = 'Сумма';

	colorScheme = {
		domain: ['#5AA454']
	};

	constructor(private pieService: PieChartService) {	}

	ngOnInit(): void {
		this.single = this.pieService.setData();
	}

	onSelect(event: any): void {
		console.log(event);
	}
}
