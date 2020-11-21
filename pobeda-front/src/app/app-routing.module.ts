import { NgModule } from '@angular/core';
import { Routes, RouterModule } from '@angular/router';
import { ChartMoneyByPeriodComponent } from './content/chart-money-by-period/chart-money-by-period.component';
import { ChartComponent } from './content/chart/chart.component';
import { CircleDiagrammComponent } from './content/circle-diagramm/circle-diagramm.component';

const routes: Routes = [
	{path: 'circle', component: CircleDiagrammComponent},
	{path: 'chart', component: ChartComponent},
	{path: 'chart-money-by-period', component: ChartMoneyByPeriodComponent},
	{path: '**', redirectTo: 'circle'}
];

@NgModule({
	imports: [RouterModule.forRoot(routes)],
	exports: [RouterModule]
})
export class AppRoutingModule { }
