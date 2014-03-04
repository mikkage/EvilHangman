#pragma once
#include <list>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class hangman
{
private:
	list<string> dictionary;	//Stores copy of entire dictionary.
	list<string> *cur;			//Stores the dynamic dictionary
	string curWord;				//Stores the uncovered current word
	string showWord;			//Stores the covered word
	string guesses;				//Stores characters that have been guessed so far.
	int remain;					//Tries remaining.
public:
	hangman();
	void showDic();
	void filterByLength(int);
	void filterByLetter(char);
	void filterByPos();
	void restoreDictionary();
	void printWord();
	bool strContains(string, char);
	void addGuess(char);
	void playGame();
	string getPrintWord();
};