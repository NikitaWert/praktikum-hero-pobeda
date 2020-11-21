import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Observable } from 'rxjs';
import { map } from 'rxjs/operators';

@Injectable({
	providedIn: 'root'
})
export class PieChartService {

	constructor(private http: HttpClient) { }

	setData(): Observable<any> {
		return this.getData()
			.pipe(
				map(data => this.convertData(data))
			);
	}

	private getData(): Observable<any> {
		return this.http.get('./assets/revenue_shelter.json');
	}

	private convertData(data: any): any {
		return data.reduce((res: { name: string, value: number, extra: any }[], item: any) => {

			res.push({ name: item.shelter, value: item.price, extra: { percents: `${Math.round(item.percent)}%`} });

			return res;
		}, []);
	}

}
