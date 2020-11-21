import { NgModule } from '@angular/core';

import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { SharedModule } from './shared/shared.module';
import { HeaderComponent } from './core/components/header/header.component';
import { MenuComponent } from './core/components/menu/menu.component';
import { CircleDiagrammComponent } from './content/circle-diagramm/circle-diagramm.component';
import { ChartComponent } from './content/chart/chart.component';
import { NgxChartsModule } from '@swimlane/ngx-charts';
import { HttpClientModule } from '@angular/common/http';
import { ChartMoneyByPeriodComponent } from './content/chart-money-by-period/chart-money-by-period.component';

@NgModule({
	declarations: [
		AppComponent,
		HeaderComponent,
		MenuComponent,
		CircleDiagrammComponent,
		ChartComponent,
		ChartMoneyByPeriodComponent
	],
	imports: [
		SharedModule,
		AppRoutingModule,
		NgxChartsModule,
		HttpClientModule
	],
	providers: [],
	bootstrap: [AppComponent]
})
export class AppModule { }
