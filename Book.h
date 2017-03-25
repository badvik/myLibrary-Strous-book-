#pragma once
#include <string>
#include <iostream>
#include "Chrono.h"
#include "Patron.h"

using namespace std;
using namespace Chrono;

enum class Genre { no_genre, dram, pros, fantas, comedy, horr };
istream& operator >> (istream& is, Genre& g);

class Book {
private:
	string isbn{ "0000-000-00-0-0" };
	string name{ "NoName" };
	string author{ "NoAuthor" };
	Date data;
	Genre gnr{ Genre::no_genre };	
	bool on_hand{ false };

public:

	Patron *book_patron; 
	void inp_isbn() { cin >> isbn; }
	void inp_name() { cin >> name; }
	void inp_author() { getline(cin, author); }
	void if_on_hand() { cin >> on_hand; }
	void inp_genre() { cin >> gnr; }	
	bool get_data();
	void on_screen();

	string show_isbn() { return isbn; }
	string show_name() { return name; }
	string show_author() { return author; }
	void show_data() { cout << data; }
	bool show_on_hand() { return on_hand; }
	Genre show_gen() { return gnr; };
	bool check_isbn();
};

ostream& operator<<(ostream& os, const Genre &g);
ostream& operator<<(ostream& os, Book &b);
bool operator==(const Book &a, Book &b);


bool Book::get_data() {
	if (data.inp_datedatas()) {
		return true;
	}
	else { 
		return false; 
	}
}
bool Book::check_isbn() {

	int count = 0;
	string str = show_isbn();
	for (size_t i = 0; i < str.size() - 1; ++i) {
		if (str[i] != '-') {
			if (!isdigit(str[i])) {
				cout << "Wrong ISBN\n";
				return false;
			}
		}
		if (str[i] == '-') {
			count++;
		}
	}
	if (!isalpha(str[str.size() - 1]) && !isdigit(str[str.size() - 1])) {
		cout << "Wrong ISBN\n";
		return false;
	}
	if (count != 3) {
		cout << "Wrong ISBN\n";
		return false;
	}
	else {
		cout << "ISBN is OK" << endl;
		return true;
	}
}
void Book::on_screen() {
	cout << "ISBN: " << show_isbn() << endl;
	cout << "Book name : " << show_name() << endl;
	cout << "It's author: " << show_author() << endl;
	cout << "Publishing data: ";
	show_data();
	cout << "\nIt is ";
	show_on_hand() ? cout << "in the library" : cout << "at somebody";
	cout << endl;
}

bool operator==(Book &a, Book &b) {
	return a.show_isbn() == b.show_isbn()
		&& a.show_author() == b.show_author()
		&& a.show_name() == b.show_name();
}

istream& operator>>(istream& is, Genre& g) {
	int tmp;
	if (is >> tmp) {
		g = Genre(tmp);
	}
	return is;
}

ostream& operator<<(ostream& os, const Genre &g) {
	string s;
	switch (g) {
	case Genre::no_genre:
		s = "No genre";
		break;
	case Genre::dram:
		s = "drama";
		break;
	case Genre::pros:
		s = "prosa";
		break;
	case Genre::fantas:
		s = "fantastic";
		break;
	case Genre::comedy:
		s = "comedy";
		break;
	case Genre::horr:
		s = "horror";
		break;
	}
	return (os << s) ;
}

ostream& operator<<(ostream& os, Book &b) {
	return os << "Book name: " << b.show_name() << endl
		<< "It's author: " << b.show_author() << endl
		<< "ISBN: " << b.show_isbn() << endl
		<< "Genre: " << b.show_gen() << endl;
}