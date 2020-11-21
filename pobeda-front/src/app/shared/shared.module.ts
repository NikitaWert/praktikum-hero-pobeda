import { LOCALE_ID, NgModule } from '@angular/core';
import { ReactiveFormsModule } from '@angular/forms';
import { BrowserModule } from '@angular/platform-browser';
import { BrowserAnimationsModule } from '@angular/platform-browser/animations';
import { MaterialModule } from './material.module';

const SHARED_MODULES = [
	BrowserModule,
	BrowserAnimationsModule,
	ReactiveFormsModule,
	MaterialModule,
];

@NgModule({
	declarations: [
	],
	imports: [
		...SHARED_MODULES,
	],
	providers: [
		{
			provide: LOCALE_ID,
			useValue: 'ru'
		}
	],
	exports: [
		...SHARED_MODULES,
	]
})
export class SharedModule { }
