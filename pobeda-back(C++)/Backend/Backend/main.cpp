#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <Windows.h>
#include <unordered_map>
#include <stdio.h>
#include "teddylib.h"

namespace fs = std::filesystem;
using namespace std;
unordered_map<string, vector<AnimalDay>> base;

void readFile(string link) {

	ifstream ip(link);
	string s;


	string first_line;
	getline(ip, first_line);

	string id;
	string house;
	string data;
	string name_price;
	string price;

	while (ip.good()) {

		getline(ip, id, ',');
		getline(ip, house, ',');

		string clearHouse;
		for (size_t i = 0; i < house.length(); i++) {
			if (house[i] != 34) clearHouse.push_back(house[i]);
		}

		getline(ip, data, ',');
		getline(ip, name_price, ',');

		string clearName_Price;
		int fistWord = 0;
		for (size_t i = 0; i < name_price.length(); i++) {
			if (name_price[i] < 32 || name_price[i] > 127) {
				fistWord = i;
				break;
			}
		}

		for (size_t i = fistWord; i < name_price.length(); i++) {
			if (name_price[i] < 33 || name_price[i] > 127) {
				if (name_price[i] == 'ё') name_price[i] = -27;
				clearName_Price.push_back(name_price[i]);
			}
		}

		if (clearName_Price == "Котодень") clearName_Price = "КотоДень";

		getline(ip, price, '\n');

		if(id == "" && house == "" && data == "" && name_price == "" && price == "") break;

		AnimalDay a(id, clearHouse, data, clearName_Price, price);

		base[clearName_Price].push_back(a);

		id.clear();
		house.clear();
		data.clear();
		name_price.clear();
		price.clear();
		clearName_Price.clear();
	}
}

void readGet() {

	ifstream f("GET.txt");

	string str;
	vector<string> table;
	vector<string> key;

	while (getline(f, str, ',')) {
		
		if (base.find(str) != base.end()) key.push_back(str);
		else table.push_back(str);

        str.clear();
	}

	make_csv(base, table, key);
}

int main() {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	string newFile = "Teddy Food Ценообразование.csv";
	string cash = "Cash.csv";

	/*
	fs::path file = newFile;
    fs::path cashLink = cash;

	if (!is_character_file(cashLink)) {
		if (is_character_file(file)) {
			copy_file(file, cashLink);
		}
	}
	*/

	ifstream file;
	file.open(newFile);
	if (file.fail()) {
		while (1) {
			file.open(newFile);
			if (!file.fail()) break;
		}
	}

	ifstream cashFile;
	cashFile.open(cash);
	if (cashFile.fail()) {
		ofstream newCash;
		newCash.open(cash);
		newCash << file.rdbuf();
	}

	readFile(cash);
	readGet();

	/*
	while (1) {

		//if (last_write_time(cashLink) < last_write_time(file)) {
	//		readFile(newFile);
			//тут надо решить каким будет новый файл, продолжением или дополнением инфы, запустить проверку обновления
	//		readGet();
	//	}

	}
	*/
	return 0;
}