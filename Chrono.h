#pragma once
#include <iostream>

using namespace std;

namespace Chrono {

	class Year {		

	public:
		Year(int x) {
			y = x;
		}
		
		int year_y() { return y; }
		static const int min = 1900;
		static const int max = 2017;

	private:
		int y;
	};
	
	enum class Month {
		jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
	};

	class Date {
	public:
		Date(Year yy, Month mm, int dd);			// конструктор с параметрами
		Date();										// конструктор по умолчанию

		Year year() { return y; }
		Month month() { return m; }
		int day() { return d; }					
		bool inp_datedatas();		

	private:
		Year y{ 2000 };								
		Month m{ Month::jan };
		int d{ 1 };
		bool isvalid();								// проверка на валидность дат

	};
	
	Date::Date(Year yy, Month mm, int dd)
		:y(yy), m(mm), d(dd)
	{
		if (!isvalid()) {
			cout << "Wrong data\n";
		}
	}

	Date::Date() {
		this->y = y;
		this->m = m;
		this->d = d;
	}
	
	istream& operator>>(istream& is, Month& i);
	
	bool Date::inp_datedatas() {					// для ввода дат
		int x;
		cout << "Input year: ";
		cin >> x; 
		y = Year::Year(x);
		cout << "Input month: ";
		cin >> m; 
		cout << "Input day: ";
		cin >> d; 
		cout << endl;
		if (!isvalid()) {
			return false;
		}
		else { 
			return true; 
		}
	}

	bool leapyear(int temp) {
		if (temp % 4 == 0) {
			return true;
		}
		else { 
			return false; 
		}
	}
	
	bool Date::isvalid() {

		if (y.year_y() < Year::min || y.year_y() > Year::max) {
			cout << "Year outside the limits\n";
			return false;
		}

		if (m < Month::jan || m > Month::dec) {
			cout << "Wrong month input\n";
			return false;
		}

		int day_in_m = 31;
		switch (m) {
		case Month::feb:
			day_in_m = (leapyear(y.year_y())) ? 29 : 28;
			break;

		case Month::apr: case Month::jul: case Month::sep: case Month::nov:
			day_in_m = 30;
			break;
		}
		if (d > day_in_m) {
			cout << "Wrong day\n";
			return false;
		}
		return true;
	}	

	istream& operator >> (istream& is, Month& i)
	{
		int tmp;
		if (is >> tmp) {
			i = Month(tmp);
		}
		return is;
	}

	ostream& operator<<(ostream& os, Date& d) {
		return os << "( " << d.year().Year::year_y()
			<< ", " << int(d.month())
			<< ", " << d.day() << " )";
	}	
}