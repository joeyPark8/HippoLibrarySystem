#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <stdlib.h>

#define lineLength 25

using namespace std;

class Hippo
{
private:
	map<int, string> borrowedBooks;

	string bookListFilePath = "data/bookList.txt";
	string borrowedBookStateFildPath = "data/borrowedBookState.txt";

	ifstream openFile;

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

	string getName(ifstream file, string str) {
		string line;
		while (getline(file, line)) {
			if (split(line)[3] == str) {
				return split(line)[5];
			}
		}

		return NULL;
	}

public:
	void load() {
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

				borrowedBooks.insert(pair<int, string>(bookNum, bookTitle));
			}
		}
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
		else if (found(borrowedBooks, books[bookNumber])) { //find(borrowedBooks.begin(), borrowedBooks.end(), bookNumber) != borrowedBooks.end()
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

		int bookNumber = askBookNumber();
		string name;

		openFile.open(borrowedBookStateFildPath);
		
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
			if (found(borrowedBooks, books[bookNumber])) {
				name = ""; //have to do it!
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
				cout << name << " borrowed " << books[bookNumber] << endl;
				borrowedBooks.insert(pair<int, string>(bookNumber, books[bookNumber]));
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
				cout << name << " returned " << books[bookNumber] << endl;
				borrowedBooks.erase(bookNumber);
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
		cout << "a. search with book title \nb. search with book number \n > ";
		cin >> userInputChar;

		if (userInputChar == 'a') {
			string bookTitle = askBookTitle();

			map<int, string> foundBook;
			
			

			cout << bookTitle << "'s booknumber is " << endl;
		}
		else if (userInputChar == 'b') {
			int bookNumber = askBookNumber();
			
			map<int, string> foundBooks;

		}
		else {

		}
	}
};

