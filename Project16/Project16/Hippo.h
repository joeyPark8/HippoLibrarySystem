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
	string borrowedBookStateFilePath = "data/borrowedBookState.txt";

public:
	map<int, string> books;
	map<int, string> peopleBorrowed;
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
	
	template<typename Type1, typename Type2>
	bool valueFound(map<Type1, Type2> m, Type2 element) {
		for (auto [key, value] : m) {
			if (value == element) {
				return true;
			}
		}

		return false;
	}

	template<typename Type1, typename Type2>
	bool keyFound(map<Type1, Type2> m, Type1 element) {
		for (auto [key, value] : m) {
			if (key == element) {
				return true;
			}
		}

		return false;
	}

	template<typename Type1>
	bool elementFound(vector<Type1> v, Type1 element) {
		for (auto value : v) {
			if (value == element) {
				return true;
			}
		}
		
		return false;
	}

	bool contain(string str1, string str2) {
		return (str1.find(str2) != string::npos);
	}

	int findVectorIndex(vector<int> v, int element) {
		int index = 0;
		for (auto i : v) {
			if (i == element) {
				return index;
			}
			index += 1;
		}

		return NULL;
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
		
		openFile.open(borrowedBookStateFilePath);
		
		if (openFile.is_open()) {
			while (getline(openFile, line)) {
				vector<string> splitedLine = split(line);

				const char* snum = splitedLine[1].c_str();
				int bookNum = atoi(snum);
				string bookTitle = splitedLine[3];
				string name = splitedLine[5];

				borrowedBookNums.push_back(bookNum);
				peopleBorrowed.insert(pair<int, string>(bookNum, name));
			}
		}

		openFile.close();
	}

	void save() {
		ofstream writer;

		writer.open(bookListFilePath);

		int count = 0;

		if (writer.is_open()) {
			for (auto [num, title] : books) {
				count += 1;
				writer << "num: " << num << " title: " << title;
				if (count != books.size()) {
					writer << endl;
				}
			}
		}

		writer.close();

		writer.open(borrowedBookStateFilePath);

		count = 0;

		if (writer.is_open()) {
			for (auto num : borrowedBookNums) {
				count += 1;
				writer << "num: " << num << " title: " << books[num] << " personBorrowed: " << peopleBorrowed[num];
				if (count != books.size()) {
					writer << endl;
				}
			}
		}

		writer.close();
	}

	void setting() {
		
		return;
	}

	void borrowBook() {
		for (int i = 0; i < lineLength; i += 1) {
			cout << '-';
			if (i == lineLength - 1) cout << endl;
		}
		cout << "borrow page" << endl;

		string name = askName();
		int bookNumber = askBookNumber();

		if (bookNumber == 0) {
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
		else if (elementFound<int>(borrowedBookNums, bookNumber)) {
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
		
		if (bookNumber == 0) {
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
			return;
		}
		else {
			if (elementFound<int>(borrowedBookNums, bookNumber)) {
				name = peopleBorrowed[bookNumber];
			}
			else {
				for (int i = 0; i < lineLength; i += 1) {
					cout << '-';
					if (i == lineLength - 1) cout << endl;
				}
				cout << books[bookNumber] << " hasn't been borrowed" << endl;
				return;
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
				cout << endl << name << " borrowed " << books[bookNumber] << endl;
				borrowedBookNums.push_back(bookNumber);
				peopleBorrowed.insert(pair<int, string>(bookNumber, name));
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

			char reply;
			cin >> reply;
			if (reply == 'y' || reply == 'Y') {
				cout << endl << name << " returned " << books[bookNumber] << endl;
				borrowedBookNums.erase(borrowedBookNums.begin() + findVectorIndex(borrowedBookNums, bookNumber));
				return;
			}
			else if (reply == 'n' || reply == 'N') {
				return;
			}
		}
		else if (type == 'd') {
			cout << "book number: " << bookNumber << endl;
			cout << "book title: " << books[bookNumber] << endl << endl;

			cout << "Do you really want to delete this book?(y/n) ";

			char reply;
			cin >> reply;
			if (reply == 'y' || reply == 'Y') {
				cout << endl << "number: " << bookNumber << ", title: " << books[bookNumber] << " is deleted" << endl;
				map<int, string>::iterator it;
				it = books.find(bookNumber);
				books.erase(it, books.end());
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
				if (elementFound<int>(borrowedBookNums, num)) {
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
				if (elementFound<int>(borrowedBookNums, num)) {
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

	void update() {
		for (int i = 0; i < lineLength; i += 1) {
			cout << '-';
			if (i == lineLength - 1) cout << endl;
		}
		cout << "update page" << endl;

		char choice;
		cout << "\n a. register new books \n b. modify books information \n c. remove book registration \n" << endl << "> ";
		cin >> choice;

		if (choice == 'a') {
			for (int i = 0; i < lineLength; i += 1) {
				cout << '-';
				if (i == lineLength - 1) cout << endl;
			}
			cout << "register new books" << endl << endl;

			string title = askBookTitle();
			int num = askBookNumber();

			if (keyFound<int, string>(books, num)) {
				cout << "This number is being used" << endl;
			}
			else {
				cout << endl << "register book title: " << title << ", number: " << num << endl;
				books.insert(pair<int, string>(num, title));
			}

			return;
		}
		else if (choice == 'b') {
			return;
		}
		else if (choice == 'c') {
			for (int i = 0; i < lineLength; i += 1) {
				cout << '-';
				if (i == lineLength - 1) cout << endl;
			}
			cout << "remove book registeration" << endl << endl;

			int num = askBookNumber();

			if (keyFound<int, string>(books, num)) {
				confirm('d', "", num);
				return;
			}
			else {
				cout << "This number isn't registered" << endl;
				return;
			}
		}
		else {
			cout << "Unvalid choice" << endl;
		}
	}
};

