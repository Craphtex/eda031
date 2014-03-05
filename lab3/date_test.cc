#include <iostream>
#include <iomanip> // for setw and setfill
#include <stdexcept>
#include <string>
#include <sstream>
#include "date.h"

using namespace std;

/*
 * Prints the date d in the format yyyy-mm-dd. You shall replace this
 * function with an overloaded operator<<, and add an overloaded operator>>.
 *
 */
void print(const Date& d) {
	cout << setw(4) << setfill('0') << d.getYear() << '-';
	cout << setw(2) << setfill('0') << d.getMonth() << '-';
	cout << setw(2) << setfill('0') << d.getDay();
}

template <typename T>
T string_cast(const string str) {
	stringstream ss;
	ss << str;
	T data;
	if(ss >> data) {
		return data;
	}
	else {
		throw std::invalid_argument("operator>> not implemented for given typename");
	}
}

template<typename T>
string toString(const T& s)
{
	stringstream ss;
	ss << s;
	string str;
	ss >> str;
	return str;
}

int main() {
	cout << "--- Testing string_cast:" << endl;
	try {
		int i = string_cast<int>("123");
		cout << i << endl;
		double d = string_cast<double>("12.34");
		cout << d << endl;
		Date date = string_cast<Date>("2013-01-10");
		cout << date << endl;
	} catch (std::invalid_argument& e) {
		cout << "Error: " << e.what() << endl;
	}

	cout << "--- Testing toString:" << endl;
	double d = 1.234;
	Date today;
	string sd = toString(d);
	string st = toString(today);
	cout << sd << endl;
	cout << st << endl;
	
	// Check 'next' by creating an object describing today's date, then
	// printing dates more than a month ahead
	cout << "--- Today and more than a month ahead:" << endl;
	Date d1;
	print(d1);
	cout << endl;
	for (int i = 1; i <= 35 ; ++i) {
		d1.next();
		print(d1);
		cout << endl;
	}
	
	// Check so 'next' functions correctly from one year to the next
	cout << "--- New Year's Eve and the next day:" << endl;
	Date d2(2013, 12, 31);
	print(d2);
	cout << endl;
	d2.next();
	print(d2);
	cout << endl;

	// Check input and output of dates. Uncomment the following when you 
	// have added operator>> and operator<<.
	bool cont = true;
	while (cont) {
		cout << "Type a date: ";
		Date aDate;
		cin >> aDate;
		if (cin.eof()) {
			cont = false;
		} else if (!cin.good()) {
			cout << "Wrong input format" << endl;
			// restore stream state and ignore the rest of the line
			cin.clear();
			cin.ignore(10000, '\n');
		}
		else {
			cout << "Output: " << aDate << endl;
		}
	}
}
