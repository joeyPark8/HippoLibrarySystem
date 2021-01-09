#include "Hippo.h"
#include <iostream>

using namespace std;

int main() {
	Hippo hippo;

	char userInputChar;
	bool first = false;
	
	while (true) {
		if (first != true) {
			first = true;
		}
		else {
			for (int i = 0; i < lineLength; i += 1) {
				cout << '-';
				if (i == lineLength - 1) cout << "\n";
			}
		}

		cout << "¢·Hippo library¢¹ \n";
		cout << "\n";
		cout << "main page \n";
		cout << "\n a. borrow \n b. return \n c. search \n d. quit \n \n> ";
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
			continue;
		}
		else if (userInputChar == 'd') {
			cout << "system turned off \n";
			break;
		}
		else {
			cout << "page cannot found \n";
			for (int i = 0; i < 25; i += 1) {
				cout << '-';
			}
			cout << "\n";
			continue;
		}
	}
	return 0;
}
