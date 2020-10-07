#include "Hippo.h"
#include <iostream>

#define bookCount 5

using namespace std;

int main() {
	char userInputChar;

	int lineLength;

	bool reCame;

	auto book1 = 1, book2 = 1, book3 = 1, book4 = 1, book5 = 1;

	string name;
	int bookNumber;

	char book[bookCount][50] = {
		"Cinderella", "Gretel", "Snow White", "Little Red Ridinghood", "Goldilocks"
	};

	int page;
	
	while (true) {
		cout << "¢·Hippo library¢¹ \n";
		cout << "\n";
		cout << "main page \n";
		cout << "\n a. borrow \n b. return \n c. quit  \n \n> ";
		cin >> userInputChar;
		page = 0;
		reCame = false;
		lineLength = 25;

		for (int i = 0; i < lineLength; i += 1) {
			cout << '-';
		}
		cout << "\n";

		if (userInputChar == 'a') {
			cout << "borrow page \n";
			page = 1;
		}
		else if (userInputChar == 'b') {
			cout << "return page \n";
			page = 2;
		}
		else if (userInputChar == 'c') {
			cout << "system turned off \n";
			break;
		}
		else {
			cout << "page cannot found \n";
			for (int i = 0; i < lineLength; i += 1) {
				cout << '-';
			}
			cout << "\n";
			continue;
		}

		while (true) {
			if (page == 1) {
				if (reCame == true) {
					for (int i = 0; i < lineLength; i += 1) {
						cout << '-';
					}
					cout << "\n";
				}

				cout << "\n your name: ";
				cin >> name;
				cout << " book number: ";
				cin >> bookNumber;

				if (bookNumber == 0) {
					break;
				}
				else if (bookNumber > bookCount || bookNumber < 0) {
					for (int i = 0; i < lineLength; i += 1) {
						cout << '-';
					}
					cout << "\n";
					cout << "book cannot found \n";
					for (int i = 0; i < lineLength; i += 1) {
						cout << '-';
					}
					cout << "\n";
				}
				else {
					for (int i = 0; i < lineLength; i += 1) {
						cout << '-';
					}
					cout << "\n";
					cout << "your name: " << name << "\n";
					cout << "book title: " << book[bookNumber - 1] << "\n";

					cout << "\nright?(y/n) : ";
					cin >> userInputChar;

					if (userInputChar == 'n') {
						reCame = true;
						continue;
					}
					else if (userInputChar == 'y') {
						break;
					}
					else {
						cout << "unknown argument";
					}
				}
			}

			else if (page == 2) {
				if (reCame == true) {
					for (int i = 0; i < lineLength; i += 1) {
						cout << '-';
					}
					cout << "\n";
				}

				cout << "\n book number: ";
				cin >> bookNumber;

				if (bookNumber == 0) {
					break;
				}
				else if (bookNumber > bookCount || bookNumber < 0) {
					for (int i = 0; i < lineLength; i += 1) {
						cout << '-';
					}
					cout << "\n";
					cout << "book cannot found \n";
					for (int i = 0; i < lineLength; i += 1) {
						cout << '-';
					}
					cout << "\n";
				}
				else {
					for (int i = 0; i < lineLength; i += 1) {
						cout << '-';
					}
					cout << "\n";
					cout << "book title: " << book[bookNumber - 1] << "\n";

					cout << "\nright?(y/n) : ";
					cin >> userInputChar;

					if (userInputChar == 'n') {
						reCame = true;
						continue;
					}
					else if (userInputChar == 'y') {
						break;
					}
					else {
						cout << "unknown argument";
					}
				}
			}

		}

		if (bookNumber == 0) {
			for (int i = 0; i < lineLength; i += 1) {
				cout << '-';
			}
			cout << "\n";
			cout << "canceled \n";
		}
		else {
			cout << "\ncomplete \n";
		}

		for (int i = 0; i < lineLength; i += 1) {
			cout << '-';
		}
		cout << "\n";

	}

	for (int i = 0; i < lineLength; i += 1) {
		cout << '-';
	}
	
	return 0;
}
