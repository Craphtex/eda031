#include <ctime>  // time and localtime
#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>
#include "date.h"

using namespace std;

int Date::daysPerMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

Date::Date() {
	time_t timer = time(0); // time in seconds since 1970-01-01
	tm* locTime = localtime(&timer); // broken-down time
	year = 1900 + locTime->tm_year;
	month = 1 + locTime->tm_mon;
	day = locTime->tm_mday;
}

Date::Date(int y, int m, int d) : year(y), month(m), day(d) {}

int Date::getYear() const {
	return year;
}

int Date::getMonth() const {
	return month;
}

int Date::getDay() const {
	return day;
}

void Date::next() {
	if (day == daysPerMonth[month-1]) {
		day = 1;
		if (month == 12) {
			month = 1;
			year += 1;
		}
		else {
			month += 1;
		}
	}
	else {
		day += 1;
	}
}

ostream& operator<<(ostream& os, const Date& date) {
	os << setw(4) << setfill('0') << date.getYear() << '-';
	os << setw(2) << setfill('0') << date.getMonth() << '-';
	os << setw(2) << setfill('0') << date.getDay();
	return os;
}

istream& operator>>(istream& is, Date& date) {
	string in;
	is >> in;
	stringstream ss;
	ss << in;
	int y, m, d;
	char c1, c2;
	ss >> y >> c1 >> m >> c2 >> d;
	if (c1 == '-' && c2 == '-'){
		date.year = y;
		date.month = m;
		date.day = d;
	}
	else {
		is.setstate(ios::failbit);
	}
	return is;
}