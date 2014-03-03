#pragma once
#include <list>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class hangman
{
private:
	list<string> dictionary;	//Stores copy of entire dictionary.
	list<string> *cur;
	string curWord;
	string showWord;
	string guesses;
	int remain;
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