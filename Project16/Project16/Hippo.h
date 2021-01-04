#pragma once
#include <iostream>
#define bookCount 5

using namespace std;

class Hippo
{	
public:
	char book[bookCount][50] = {
		"Cinderella", "Gretel", "Snow White", "Little Red Ridinghood", "Goldilocks"
	};

private:
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

		return bookNumber;
	}

public:
	void borrowBook() {
		cout << "borrow page \n";

		string name = askName();
		int bookNumber = askBookNumber();

		if (bookNumber == 0) {
			return;
		}
		else if (bookNumber < 0 || bookCount < bookNumber) {

		}
		else {

		}
	}

	void returnBook() {

	}
};

