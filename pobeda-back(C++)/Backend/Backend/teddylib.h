#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

struct Time {

private:
	int year;
	int month;
	int day;
	int hour;
	int min;
	int sec;

public:

	void push(int year, int month, int day, int hour, int min, int sec);
	void push(string& time);
	int get_year();
	int get_month();
	int get_day();
	int get_hour();
	int get_min();
	int get_sec();
	bool comparisonTime(Time a, Time b);
};

class AnimalDay {

private:
	int id_client;
	string name_house;
	Time data;
	string name_price;
	double price;

public:

	AnimalDay();
	AnimalDay(string& id, string& name, string& time, string& name_price, string& price);
	void push(int& id, string& name, string& time, string& name_price, double& price);
	//void make_csv(unordered_map<string, vector<AnimalDay*>>& base);
	int get_id_client();
	string get_name_house();
	void get_data(string& m, string& oc);
	string get_name_price();
	double get_price();
	Time getTime();
};

void make_csv(unordered_map<string, vector<AnimalDay>>& base, vector<string>& table, vector<string>& key);