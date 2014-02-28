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
	list<string> curDictionary;	//Stores the filtered version of the dictionary.
	string curWord;
	string guesses;
	int remain;
public:
	hangman();
	void showDic();
	void filterByLength(int);
	void filterByLetter(char);
	void restoreDictionary();
	void printWord();
	bool strContains(string, char);
	void addGuess(char);

	void setWord(string);
	void setGuesses(string);
};