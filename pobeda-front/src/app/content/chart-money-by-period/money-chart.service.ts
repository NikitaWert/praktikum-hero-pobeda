import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Observable, Subject } from 'rxjs';
import { map, tap } from 'rxjs/operators';

@Injectable({
	providedIn: 'root'
})
export class MoneyChartService {

	constructor(private http: HttpClient) { }

	setData(): Observable<any> {
		return this.getData()
			.pipe(
				map(data => this.convertData(data))
			);
	}

	private getData(): Observable<any> {
		return this.http.get('./assets/revenue_date.json');
	}

	private convertData(data: any): any {

		return data.reduce((res: { name: string, value: number }[], item: any) => {

			res.push({ name: new Date(item.date).toDateString(), value: item.price });

			return res;
		}, []);
	}

}
