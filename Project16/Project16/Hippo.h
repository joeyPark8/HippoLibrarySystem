#pragma once
#include <iostream>
#include <vector>
#include <map>
#define bookCount 5
#define lineLength 25

using namespace std;

class Hippo
{	
public:
	char book[bookCount][50] = {
		"Cinderella", "Gretel", "Snow White", "Little Red Ridinghood", "Goldilocks"
	};

private:
	vector<int> borrowedBooks;
	map<int, string> state;

	string askName() {
		string name = " ";

		cout << "\n your name: ";
		cin >> name;

		return name;
	}

	int askBookNumber() {
		int bookNumber = 0;

		cout << " book number: ";
		cin >> bookNumber;

		return bookNumber + 1;
	}

public:
	void borrowBook() {
		for (int i = 0; i < lineLength; i += 1) {
			cout << '-';
			if (i == lineLength - 1) cout << "\n";
		}
		cout << "borrow page \n";

		string name = askName();
		int bookNumber = askBookNumber();

		if (bookNumber == 0) {
			for (int i = 0; i < lineLength; i += 1) {
				cout << '-';
				if (i == lineLength - 1) cout << "\n";
			}
			cout << "it is canceled" << endl;
			return;
		}
		else if (bookNumber < 0 || bookCount < bookNumber) {
			for (int i = 0; i < lineLength; i += 1) {
				cout << '-';
				if (i == lineLength - 1) cout << "\n";
			}
			cout << "Cannot find the book" << "\n";
			borrowBook();
		}
		else {
			confirm('b', name, bookNumber);
		}
	}

	void returnBook() {
		for (int i = 0; i < lineLength; i += 1) {
			cout << '-';
			if (i == lineLength - 1) cout << "\n";
		}
		cout << "return page" << "\n \n";

		int bookNumber = askBookNumber();
		string name;
		
		if (bookNumber == 0) {
			for (int i = 0; i < lineLength; i += 1) {
				cout << '-';
				if (i == lineLength - 1) cout << "\n";
			}
			cout << "it is canceled" << endl;
			return;
		}
		else if (bookNumber < 0 || bookNumber > bookCount) {
			for (int i = 0; i < lineLength; i += 1) {
				cout << '-';
				if (i == lineLength - 1) cout << "\n";
			}
			cout << "Cannot find the book";
			for (int i = 0; i < lineLength; i += 1) {
				cout << '-';
				if (i == lineLength - 1) cout << "\n";
			}
			returnBook();
		}
		else {
			if (find(borrowedBooks.begin(), borrowedBooks.end(), bookNumber) != borrowedBooks.end()) {
				name = state[bookNumber];
			}
			else {
				for (int i = 0; i < lineLength; i += 1) {
					cout << '-';
					if (i == lineLength - 1) cout << "\n";
				}
				cout << book[bookNumber] << " hasn't been borrowed" << "\n";
				returnBook();
			}
			confirm('r', name, bookNumber);
		}
	}

	void confirm(char type, string name, int bookNumber) {
		for (int i = 0; i < lineLength; i += 1) {
			cout << '-';
			if (i == lineLength - 1) cout << "\n";
		}
		cout << "confirm page" << endl << endl;

		if (type == 'b') {
			cout << "your name: " << name << "\n";
			cout << "book title: " << book[bookNumber] << "\n \n";

			cout << "Is all right?(y/n) ";

			char reply = ' ';
			cin >> reply;
			if (reply == 'y' || reply == 'Y') {
				cout << name << " borrowed " << book[bookNumber] << "\n";
				state.insert(pair<int, string>(bookNumber, name));
				borrowedBooks.push_back(bookNumber);
				return;
			}
			else if (reply == 'n' || reply == 'N') {
				return;
			}
		}
		else if (type == 'r') {
			cout << "your name: " << name << "\n";
			cout << "book title: " << book[bookNumber] << "\n" << endl;

			cout << "Is all right?(y/n) ";

			char reply = ' ';
			cin >> reply;
			if (reply == 'y' || reply == 'Y') {
				cout << name << " returned " << book[bookNumber] << endl;
				state.erase(bookNumber);
				borrowedBooks.erase(borrowedBooks.begin() + (find(borrowedBooks.begin(), borrowedBooks.end(), bookNumber) - borrowedBooks.begin()));
				return;
			}
			else if (reply == 'n' || reply == 'N') {
				return;
			}
		}
	}
};

