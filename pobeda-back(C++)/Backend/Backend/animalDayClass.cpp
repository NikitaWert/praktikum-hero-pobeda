#include <iostream>
#include <string>
#include <vector>
#include "teddylib.h"
#include <fstream>
#include <filesystem>
#include <unordered_map>
#include <algorithm>

using namespace std;


	void Time::push(int year, int month, int day, int hour, int min, int sec) {
		this->year = year;
		this->month = month;
		this->day = day;
		this->hour = hour;
		this->min = min;
		this->sec = sec;
	}

	void Time::push(string& time) {

		vector<int> t;
		string str;

		for (size_t i = 0; i < time.length(); i++) {
			if (time[i] > 47 && time[i] < 58) {
				str.push_back(time[i]);
			}
			else {
				t.push_back(stoi(str));
				str.clear();
			}
		}
		t.push_back(stoi(str));
		push(t[0], t[1], t[2], t[3], t[4], t[5]);
	}

	int Time::get_year() {
		return year;
	}

	int Time::get_month() {
		return month;
	}

	int Time::get_day() {
		return day;
	}

	int Time::get_hour() {
		return hour;
	}

	int Time::get_min() {
		return min;
	}

	int Time::get_sec() {
		return sec;
	}

	bool Time::comparisonTime(Time a, Time b) {
		if (b.get_year() > a.get_year()) { 
			return true;
		}
		else if (b.get_year() == a.get_year()) {
			if (b.get_month() > a.get_month()) {
				return true;
			}
			else if (b.get_month() == a.get_month()) {
				if (b.get_day() > a.get_day()) {
					return true;
				}
				else if (b.get_day() == a.get_day()) {
					if (b.get_hour() > a.get_hour()) {
						return true;
					}
					else if (b.get_hour() == a.get_hour()) {
						if (b.get_min() > a.get_min()) {
							return true;
						}
						else if (b.get_min() == a.get_min()) {
							if (b.get_sec() > a.get_sec()) {
								return true;
							}
							else {
								return false;
							}
						}
					}
				}
			}
		}
		return false;
	}

	AnimalDay::AnimalDay(){}

	AnimalDay::AnimalDay(string& id, string& name, string& time, string& name_price, string& price) {
		id_client = stoi(id);
		name_house = name;
		data.push(time);
		this->name_price = name_price;
		this->price = stod(price);
	}

	void AnimalDay::push(int& id, string& name, string& time, string& name_price, double& price) {
		id_client = id;
		name_house = name;
		data.push(time);
		this->name_price = name_price;
		this->price = price;
	}

	int AnimalDay::get_id_client() {
		return id_client;
	}

	string AnimalDay::get_name_house() {
		return name_house;
	}
	void AnimalDay::get_data(string& m, string& oc) {
		m = to_string(data.get_year()) + '-' + to_string(data.get_month()) + '-' + to_string(data.get_day());
		oc = to_string(data.get_hour()) + ':' + to_string(data.get_min()) + ':' + to_string(data.get_sec());
	}

	string AnimalDay::get_name_price() {
		return name_price;
	}

	double AnimalDay::get_price() {
		return price;
	}

	Time AnimalDay::getTime() {
		return data;
	}

	bool comp(AnimalDay& a, AnimalDay& b) {
		
		if (a.get_name_price() == b.get_name_price()) {
			return a.getTime().comparisonTime(a.getTime(), b.getTime());
		}
		return false;
	}

	void make_csv(unordered_map<string, vector<AnimalDay>>& base, vector<string>& table, vector<string>& key) {

		string str;

		vector<AnimalDay> forCsv;

		for (size_t i = 0; i < key.size(); i++) {
			for (size_t f = 0; f < base[key[i]].size(); f++) {
				forCsv.push_back(base[key[i]][f]);
			}
		}

		sort(forCsv.begin(), forCsv.end(), comp);

		while (1) {

			ofstream check_file;
			check_file.open("table.csv");
			check_file.close();

			if (!check_file.fail()) {


				filesystem::remove("table.csv");
				ofstream myfile;
				myfile.open("table.csv");


				//Идентификатор пользователя,"Название приюта","Дата/время платежа","Наименование услуги","Сумма платежа"
				for (size_t i = 0; i < table.size(); i++) {
					if (table[i] == "id") {
						str += "Идентификатор пользователя";
					    str += ',';
					}
					else if (table[i] == "name_house") {
						str += "Название приюта";
						str += ',';
					}
					else if (table[i] == "purchase_date") {
						str += "Дата/время платежа";
						str += ',';
					}
					else if (table[i] == "name_price") {
						str += "Наименование услуги";
						str += ',';
					}
					else if (table[i] == "price") {
						str += "Сумма платежа";
						str += ',';
					}
				}

				str[str.length() - 1] = '\n';
				myfile << str;
				str.clear();

				for (size_t f = 0; f < forCsv.size(); f++) {
					for (size_t i = 0; i < table.size(); i++) {
						if (table[i] == "id") {
							str += to_string(forCsv[f].get_id_client());
							str += ',';
						}
						else if (table[i] == "name_house") {
							str += forCsv[f].get_name_house();
							str += ',';
						}
						else if (table[i] == "data") {
							string d;
							string oc;

							forCsv[f].get_data(d, oc);
							str += d;
							str += ',';
							str += oc;
							str += ',';
						}
						else if (table[i] == "purchase_date") {
							string d;
							string oc;

							forCsv[f].get_data(d, oc);
							str += d;
							str += ' ';
							str += oc;
							str += ',';
						}
						else if (table[i] == "name_price") {
							str += forCsv[f].get_name_price();
							str += ',';
						}
						else if (table[i] == "price") {
							str += to_string((int)forCsv[f].get_price());
							str += ',';
						}
						else if (table[i] == "year") {
							str += forCsv[f].get_name_house();
							str += ',';
						}
					}
					str[str.length()-1] = '\n';
					myfile << str;
					str.clear();
				}
				myfile.close();
				break;
			}
		}
	}
