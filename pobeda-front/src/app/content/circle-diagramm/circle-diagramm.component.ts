import { Component, OnInit, TemplateRef, ViewChild } from '@angular/core';
import { Observable } from 'rxjs';
import { PieChartService } from './pie-chart.service';

@Component({
	selector: 'app-circle-diagramm',
	templateUrl: './circle-diagramm.component.html',
	styleUrls: ['./circle-diagramm.component.scss']
})
export class CircleDiagrammComponent implements OnInit {

	@ViewChild('to') tooltipTemplate: TemplateRef<any>;

	single: Observable<any>;
	view: [number, number] = [1000, 400];

	gradient = false;
	showLegend = true;
	showLabels = true;
	isDoughnut = true;

	constructor(private pieService: PieChartService) {}

	ngOnInit(): void {
		this.single = this.pieService.setData();
	}

	onSelect(data: any): void {
		// console.log('Item clicked', JSON.parse(JSON.stringify(data)));
	}

	onActivate(data: any): void {
		// console.log('Activate', JSON.parse(JSON.stringify(data)));
	}

	onDeactivate(data: any): void {
		// console.log('Deactivate', JSON.parse(JSON.stringify(data)));
	}

	tooltipText(e: any): string {
		return e.data.extra.percents;
	}

}
