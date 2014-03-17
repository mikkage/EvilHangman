//Note that this has only been tested to work in Visual Studio 2012.
//May not compile and or work correctly on other platforms/compilers.
#pragma once
#include <list>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class hangman
{
private:
	string curWord;				//Stores the uncovered current word
	string showWord;			//Stores the covered word
	string guesses;				//Stores characters that have been guessed so far.
	int remain;					//Tries remaining.
	string *dict;
	int dictLen;
	string *curDict;
	int curLen;
	string *dict1;
public:
	hangman();
	void showDic();
	void filterLength(int);
	void filterLetter(char);
	void filterPos();
	void restoreDictionary();
	void printWord();
	bool elem(string, char);
	void addGuess(char);
	void playGame();
	string getPrintWord();
	string intersperse(string, char);
};