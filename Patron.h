#pragma once
#include <string>
#include <iostream>

using namespace std;

class Patron {
private:
	string name{ "NoName"};
	int id_card{0};
	int memb_fee{0};
	const int ann_fee = 100;

public:
	void get_name() { getline(cin, name); }
	void get_id_card() { cin >> id_card; }
	void get_memb_fee() { cin >> memb_fee; }

	string show_name() { return name; }
	int show_id() { return id_card; }
	int show_fee() { return memb_fee; }

	bool check_pay();

};

bool Patron::check_pay() {
	if (memb_fee < ann_fee) {
		return false;
	}
	else return true;
}

ostream& operator<<(ostream& os, Patron &p) {
	string s;
	if (p.check_pay()) {
		s = "paid";
	}
	else {
		s = "WARNING NOT paid";
	}
	return os << "Member name: " << p.show_name()
		<< ", member ID: " << p.show_id()
		<< "\nfee is " << s << endl;
}
