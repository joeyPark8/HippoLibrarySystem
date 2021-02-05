#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <stdlib.h>

#define lineLength 50

using namespace std;

class Hippo
{
private:
	vector<int> borrowedBookNums;

	string bookListFilePath = "data/bookList.txt";
	string borrowedBookStateFildPath = "data/borrowedBookState.txt";

public:
	map<int, string> books;

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

	string askBookTitle() {
		string bookTitle;

		cout << " book title: ";
		cin >> bookTitle;

		return bookTitle;
	}

	vector<string> split(string str) {
		vector<string> splitedString;
		string word;
		int count = 0;
		for (char i : str) {
			count += 1;
			if (i != ' ' && count != str.length()) {
				word += i;
			}
			else {
				if (count == str.length()) word += i;
				splitedString.push_back(word);
				word = "";
			}
		}

		return splitedString;
	}

	bool found(map<int, string> m, string str) {
		for (auto [num, title] : m) {
			if (title == str) {
				return true;
			}
		}

		return false;
	}

	bool vfound(vector<int> m, int i) {
		for (auto num : m) {
			if (num == i) {
				return true;
			}
		}

		return false;
	}

	bool contain(string str1, string str2) {
		return (str1.find(str2) != string::npos);
	}

public:
	void load() {
		ifstream openFile;

		openFile.open(bookListFilePath);
		string line;

		if (openFile.is_open()) {
			while (getline(openFile, line)) {
				vector<string> splitedLine = split(line);

				const char* snum = splitedLine[1].c_str();
				int bookNum = atoi(snum);
				string bookTitle = splitedLine[3];

				books.insert(pair<int, string>(bookNum, bookTitle));
			}
		}

		openFile.close();
		
		openFile.open(borrowedBookStateFildPath);
		
		if (openFile.is_open()) {
			while (getline(openFile, line)) {
				vector<string> splitedLine = split(line);

				const char* snum = splitedLine[1].c_str();
				int bookNum = atoi(snum);
				string bookTitle = splitedLine[3];

				borrowedBookNums.push_back(bookNum);
			}
		}
	}

	void update() {
		ofstream writer;

		writer.open(bookListFilePath);

		if (writer.is_open()) {
			for (auto [num, title] : books) {
				writer << num << "";
			}
		}

		writer.close();
	}

	void borrowBook() {
		for (int i = 0; i < lineLength; i += 1) {
			cout << '-';
			if (i == lineLength - 1) cout << endl;
		}
		cout << "borrow page" << endl;

		string name = askName();
		int bookNumber = askBookNumber();

		if (bookNumber == -1) {
			for (int i = 0; i < lineLength; i += 1) {
				cout << '-';
				if (i == lineLength - 1) cout << endl;
			}
			cout << "it is canceled" << endl;
			return;
		}
		else if (bookNumber < 0 || books.size() < bookNumber) {
			for (int i = 0; i < lineLength; i += 1) {
				cout << '-';
				if (i == lineLength - 1) cout << endl;
			}
			cout << "Cannot find the book" << endl;
			borrowBook();
		}
		else if (vfound(borrowedBookNums, bookNumber)) {
			for (int i = 0; i < lineLength; i += 1) {
				cout << '-';
				if (i == lineLength - 1) cout << endl;
			}
			cout << "This book has been already borrowed" << endl;
		}
		else {
			confirm('b', name, bookNumber);
		}
	}

	void returnBook() {
		for (int i = 0; i < lineLength; i += 1) {
			cout << '-';
			if (i == lineLength - 1) cout << endl;
		}
		cout << "return page" << endl << endl;

		ifstream openStateFile;
		openStateFile.open(borrowedBookStateFildPath);

		int bookNumber = askBookNumber();
		string name;
		
		if (bookNumber == -1) {
			for (int i = 0; i < lineLength; i += 1) {
				cout << '-';
				if (i == lineLength - 1) cout << endl;
			}
			cout << "it is canceled" << endl;
			return;
		}
		else if (bookNumber < 0 || bookNumber > books.size()) {
			for (int i = 0; i < lineLength; i += 1) {
				cout << '-';
				if (i == lineLength - 1) cout << endl;
			}
			cout << "Cannot find the book" << endl;
			returnBook();
		}
		else {
			if (vfound(borrowedBookNums, bookNumber)) {
				string line;
				if (openStateFile.is_open()) {
					while (getline(openStateFile, line)) {
						vector<string> splitedLine = split(line);
						if (splitedLine[3] == books[bookNumber]) {
							name = splitedLine[5];
						}
					}
				}
			}
			else {
				for (int i = 0; i < lineLength; i += 1) {
					cout << '-';
					if (i == lineLength - 1) cout << endl;
				}
				cout << books[bookNumber] << " hasn't been borrowed" << endl;
				returnBook();
			}
			confirm('r', name, bookNumber);
		}

		openStateFile.close();
	}

	void confirm(char type, string name, int bookNumber) {
		for (int i = 0; i < lineLength; i += 1) {
			cout << '-';
			if (i == lineLength - 1) cout << endl;
		}
		cout << "confirm page" << endl << endl;

		if (type == 'b') {
			cout << "your name: " << name << endl;
			cout << "book title: " << books[bookNumber] << endl << endl;

			cout << "Is all right?(y/n) ";

			char reply = ' ';
			cin >> reply;
			if (reply == 'y' || reply == 'Y') {
				cout << endl << name << " borrowed " << books[bookNumber] << endl;
				borrowedBookNums.push_back(bookNumber);
				return;
			}
			else if (reply == 'n' || reply == 'N') {
				return;
			}
		}
		else if (type == 'r') {
			cout << "your name: " << name << endl;
			cout << "book title: " << books[bookNumber] << endl << endl;

			cout << "Is all right?(y/n) ";

			char reply = ' ';
			cin >> reply;
			if (reply == 'y' || reply == 'Y') {
				cout << endl << name << " returned " << books[bookNumber] << endl;
				borrowedBookNums.erase(borrowedBookNums.begin());
				return;
			}
			else if (reply == 'n' || reply == 'N') {
				return;
			}
		}
	}

	void search() {
		for (int i = 0; i < lineLength; i += 1) {
			cout << '-';
			if (i == lineLength - 1) cout << endl;
		}
		cout << "search page" << endl;

		char userInputChar;
		cout << "\n a. search with book title \n b. search with book number \n\n> ";
		cin >> userInputChar;

		if (userInputChar == 'a') {
			for (int i = 0; i < lineLength; i += 1) {
				cout << '-';
				if (i == lineLength - 1) cout << endl;
			}
			cout << "search page" << endl << endl;

			string bookTitle = askBookTitle();

			for (int i = 0; i < lineLength; i += 1) {
				cout << '-';
				if (i == lineLength - 1) cout << endl;
			}
			cout << "results" << endl << endl;

			map<int, string> foundBook;
			
			for (auto [num, title] : books) {
				if (contain(title, bookTitle)) {
					foundBook.insert(pair<int, string>(num, title));
				}
			}

			for (auto [num, title] : foundBook) {
				if (vfound(borrowedBookNums, num)) {
					cout << "number: " << num << ", title: " << title << ", state: unavilable" << endl;
				}
				else {
					cout << "number: " << num << ", title: " << title << ", state: avilable" << endl;
				}
			}
		}
		else if (userInputChar == 'b') {
			for (int i = 0; i < lineLength; i += 1) {
				cout << '-';
				if (i == lineLength - 1) cout << endl;
			}
			cout << "search page" << endl << endl;

			int bookNumber = askBookNumber();
			
			for (int i = 0; i < lineLength; i += 1) {
				cout << '-';
				if (i == lineLength - 1) cout << endl;
			}
			cout << "results" << endl << endl;

			map<int, string> foundBooks;

			for (auto [num, title] : books) {
				if (bookNumber == num) {
					foundBooks.insert(pair<int, string>(num, title));
				}
			}

			for (auto [num, title] : foundBooks) {
				if (vfound(borrowedBookNums, num)) {
					cout << "number: " << num << ", title: " << title << ", state: unavilable" << endl;
				}
				else {
					cout << "number: " << num << ", title: " << title << ", state: avilable" << endl;
				}
			}
		}
		else {
			cout << "Unvalid choice" << endl;
		}
	}

	void modify() {
		for (int i = 0; i < lineLength; i += 1) {
			cout << '-';
			if (i == lineLength - 1) cout << endl;
		}
		cout << "update page" << endl;

		char choice;
		cout << "\n a. register new books \n b. modify books information \n c. remove book registration \n" << endl << "> ";
		cin >> choice;

		if (choice == 'a') {
			return;
		}
		else if (choice == 'b') {
			return;
		}
		else if (choice == 'c') {
			return;
		}
		else {
			cout << "Unvalid choice" << endl;
		}
	}
};

