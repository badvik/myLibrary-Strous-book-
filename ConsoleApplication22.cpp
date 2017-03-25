#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include "Book.h"
#include "Patron.h"

using namespace Chrono;
using namespace std;

class Library {
private:
	vector<Book> library;
	vector<Patron> members;	
		
public:

	void add_book();
	void books_overview();
	void edit_book();
	void add_member();
	void members_overview();
	void edit_memb();

};

bool check_doubles(Book &obj, vector<Book> &library);
void Library::add_book() {
	char ch;
	do {
		Book *obj = new Book();
		bool flag = false;
		do {
			cout << "Input the ISBN\n";
			(*obj).inp_isbn();
			cout << "Checking the ISBN...\n";
			flag = (*obj).check_isbn();
		} while (!flag);
		cout << "Input the name\n";
		(*obj).inp_name();
		cin.get();
		cout << "Input an Author\n";
		(*obj).inp_author();
		bool flag2 = true;
		do {
			cout << "Input the Date\n";
			flag = (*obj).get_data();
		} while (!flag);
		cout << "Is it in on hand: true(1) or false(0)\n";
		(*obj).if_on_hand();
		if ((*obj).show_on_hand()) {
			if (members.size() != 0) {
				int mem_id;
				cout << "Input member ID\n";
				cin >> mem_id;
				for (size_t i = 0; i < members.size(); ++i) {
					if (mem_id == members[i].show_id()) {
						(*obj).book_patron = &members[i];
						cout << "Member is found it is: \n" << *((*obj).book_patron);
						return;
					}
					else {
						cout << "Member is not found or no exists\n";
					}
				}				
			}
			else {
				cout << "Members list is empty\n";
			}
		}
		cout << "Input the genre: no_genre (0), drama (1), prosa(2),"
			<< "fantastic(3), comedy(4), horror(5)";
		(*obj).inp_genre();
		if (library.size() == 0) {
			library.push_back(*obj);
			delete obj;
		}
		else {
			cout << "Checking for doubles...\n";
			if (!check_doubles(*obj, library)) {
				cout << "OK\n";
				library.push_back(*obj);
				delete obj;
			}
			else {
				cout << "such book already exists\n";
				delete obj;
			}
		}
		cout << "Do you want to add another book y or n?\n";
		cin >> ch;
	} while (ch != 'n' && ch != 'N');
}
void Library::books_overview() {
	cout << "Do you want to see all books(0), search by ISBN(1) or display all books on hand (2)?" 
		<< "\nTo quit input 'Q'\n";
	char ch;
	cin >> ch;
	if (ch == '0') {
		if (library.size() != 0) {
			for (size_t i = 0; i < library.size(); ++i) {
				cout << "Book #" << i + 1 << ": " << endl;
				cout << library[i];
			}
		}
		else {
			cout << "There are no books in the library\n";
			return;
		}
	}
	else if (ch == '1') {
		string isbn_search;
		cout << "Input ISBN to find: ";
		cin >> isbn_search;
		for (size_t i = 0; i < library.size(); ++i) {
			if (isbn_search == library[i].show_isbn())
				cout << library[i];
			return;
		}
	}
	else if (ch == '2') {
		bool flag3 = false;
		for (auto i : library) {
			if (i.show_on_hand()) {
				cout << i << endl;
				flag3 = true;
			}			
		}
		if (!flag3) {
			cout << "There are no books on hands\n";
		}
	}
	else if (ch == 'q' || ch == 'Q') {
		return;
	}
	else cout << "Wrong input\n";
}
void Library::edit_book() {
	if (library.size() == 0) {
		cout << "List of books is empty\n";
		return;
	}
	string edit_isbn;
	cout << "Input the book ISBN to be edited: ";
	cin >> edit_isbn;
	for (size_t i = 0; i < library.size(); ++i) {
		if (edit_isbn == library[i].show_isbn()) {
			bool flag = false;
			do {
				cout << "Input the ISBN\n";
				library[i].inp_isbn();
				cout << "Checking the ISBN...\n";
				flag = library[i].check_isbn();
			} while (!flag);
			cout << "Input the name\n";
			library[i].inp_name();
			cin.get();
			cout << "Input an Author\n";
			library[i].inp_author();			
			cout << "Is it in the library: true(1) or false(0)\n";
			library[i].if_on_hand();
			if ((library[i].show_on_hand())) {
				int mem_id;
				cout << "Input member ID\n";
				cin >> mem_id;
				for (size_t i = 0; i < members.size(); ++i) {
					if (mem_id == members[i].show_id()) {
						(library[i]).book_patron = &members[i];
					}
				}
				cout << "Member is found it is: \n" << *(library[i].book_patron);
			}
			cout << "Input the genre no_genre (0), drama (1), prosa(2),"
				<< "fantastic(3), comedy(4), horror(5)";
			library[i].inp_genre();
			cout << "Checking for doubles...\n";
			if (!check_doubles(library[i], library)) {
				cout << "OK\n";				
			}
			else {
				cout << "such book already exists\n";				
			}		
		}
		else {
			cout << "Oops, there is no such book\n";
		}
	}
}
void Library::add_member() {
	Patron *member = new Patron();
	cout << "Input member name: ";
	cin.get();
	(*member).get_name();
	cout << "Input it's card: ";
	(*member).get_id_card();
	cout << "Input total paid fee: ";
	(*member).get_memb_fee();
	cout << "Now checking fee payment...";
	if ((*member).check_pay()) {
		cout << "OK\n";
	}
	else cout << "WARNING: Fee is not paid\n";
	members.push_back(*member);
	delete member;
}
void Library::members_overview() {
	cout << "Do you want to see all members(0) or search by ID(1)? For exit press 'q'\n";
	char ch;
	cin >> ch;
	if (ch == '0') {
		if (members.size() != 0) {
			for (size_t i = 0; i < members.size(); ++i) {
				cout << "Book #" << i + 1 << ": " << endl;
				cout << members[i];
			}
		}
		else {
			cout << "Members list is empty\n";
			return;
		}
	}
	else if (ch == '1') {
		if (members.size() != 0) {
			int id_search;
			cout << "Input ID to find: ";
			cin >> id_search;
			for (size_t i = 0; i < members.size(); ++i) {
				if (id_search == members[i].show_id()) {
					cout << members[i];
					return;
				}
				else {
					cout << "Member is not found or no exists\n";
					return;
				}
			}
		}
		else {
			cout << "Members list is empty\n";
		}
	}
	else if (ch == 'Q' || ch == 'q') {
		return;
	}
	else cout << "Wrong input\n";
}
void Library::edit_memb() {
	if (members.size() == 0) {
		cout << "List of members is empty\n";
		return;
	}
	cout << "Input member ID to be edited: ";
	int id_edit;
	cin >> id_edit;
	for (size_t i = 0; i < members.size(); ++i) {
		if (id_edit == members[i].show_id()) {
			cout << "Input member name: ";
			cin.get();
			members[i].get_name();
			cout << "Input it's card: ";
			members[i].get_id_card();
			cout << "Input total paid fee: ";
			members[i].get_memb_fee();
			cout << "Now checking fee payment...";
			if (members[i].check_pay()) {
				cout << "OK\n";
			}
			else cout << "WARNING: Fee is not paid\n";
		}
	}
}

int main()
{
	setlocale(LC_ALL, "rus");
	Library our_library;
	char ch;
	
	cout << "_____________State Library #1____________\n";
	do {
		cout << "What do you want to do ('Q' to quit):\n"
			<< "Add book (0)" << ", Find book or overview the books (1)" << ", Edit a book (2)\n" 
			<< "Add member (3)" << ", Find member or overview the members (4)" 
			<< "Edit a member (5)\n";
		cin >> ch;
		switch (ch) {
		case '0':
			our_library.add_book();
			break;
		case '1':
			our_library.books_overview();
			break;
		case '2':
			our_library.edit_book();
			break;
		case '3':
			our_library.add_member();
			break;
		case '4':
			our_library.members_overview();
			break;
		case '5':
			our_library.edit_memb();
			break;
		}		
	} while (ch != 'q' && ch != 'Q');	 
}

bool check_doubles(Book &obj, vector<Book> &library) {
	for (size_t i = 0; i < library.size(); ++i) {
		if (obj == library[i]) return true;
	}
	return false;
}
