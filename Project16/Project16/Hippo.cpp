#include "Hippo.h"
#include <iostream>

using namespace std;

int main() {
	Hippo hippo;

	char userInputChar;
	bool first = false;

	hippo.load();

	for (auto [num, title] : hippo.books) {
		cout << "num: " << num << ", title: " << title << endl;
	}
	cout << endl;
	
	while (true) {
		if (first != true) {
			first = true;
		}
		else {
			for (int i = 0; i < lineLength; i += 1) {
				cout << '-';
				if (i == lineLength - 1) cout << endl;
			}
		}

		cout << "¢·Hippo library¢¹ \n";
		cout << "\n";
		cout << "main page \n";
		cout << "\n a. borrow \n b. return \n c. search \n d. modify \n e. quit \n \n> ";
		cin >> userInputChar;
		
		if (userInputChar == 'a') {
			hippo.borrowBook();
			continue;
		}
		else if (userInputChar == 'b') {
			hippo.returnBook();
			continue;
		}
		else if (userInputChar == 'c') {
			hippo.search();
			continue;
		}
		else if (userInputChar == 'd') {
			hippo.modify();
			continue;
		}
		else if (userInputChar == 'e') {
			for (int i = 0; i < lineLength; i++) {
				cout << '-';
				if (i == lineLength - 1) cout << endl;
			}
			cout << "system turned off" << endl;
			break;
		}
		else {
			for (int i = 0; i < lineLength; i += 1) {
				cout << '-';
				if (i == lineLength - 1) cout << endl;
			}
			cout << "page cannot found " << endl;
			continue;
		}
	}
	return 0;
}
