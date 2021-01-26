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
	string bookListFilePath = "data/bookList.txt";

	ifstream openFile;

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

public:
	/*
	char book[bookCount][50] = {
		"Cinderella", "Gretel", "Snow White", "Little Red Ridinghood", "Goldilocks"
	};
	*/
	
	map<int, string> books;

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

		return bookNumber;
	}

	string askBookTitle() {
		string bookTitle;

		cout << " book title: ";
		cin >> bookTitle;

		return bookTitle;
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
				string bookTitle = splitedLine[splitedLine.size() - 1];

				books.insert(pair<int, string>(bookNum, bookTitle));
			}
		}

		openFile.close();
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
		else if (find(borrowedBooks.begin(), borrowedBooks.end(), bookNumber) != borrowedBooks.end()) {
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
			if (find(borrowedBooks.begin(), borrowedBooks.end(), bookNumber) != borrowedBooks.end()) {
				name = state[bookNumber];
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
				state.insert(pair<int, string>(bookNumber, name));
				borrowedBooks.push_back(bookNumber);
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
				state.erase(bookNumber);
				borrowedBooks.erase(borrowedBooks.begin() + (find(borrowedBooks.begin(), borrowedBooks.end(), bookNumber) - borrowedBooks.begin()));
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

			map<string, string> foundBook;
			
			
			for (auto [num, title] : books) {
				if (bookTitle == title) {
					
				}
			}

			cout << bookTitle << "'s booknumber is " << endl;
		}
		else if (userInputChar == 'b') {
			int bookNumber = askBookNumber();
			
			map<int, string> foundBooks;

			for (auto i : books) {
				
			}
		}
		else {

		}
	}
};

