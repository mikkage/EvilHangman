#include "hangman.h"
hangman::hangman()
{
	//initialize dictionary list
	string in;
	fstream fin;
	fin.open("dictionary.txt");
	cout << "Loading dictionary...";
	while(!fin.eof())
	{
		fin >> in;
		dictionary.push_back(in);
	}
	fin.close();
	cout << "Done" << endl;
	guesses = "";
}
void hangman::showDic()
{
	for(list<string>::iterator it = curDictionary.begin(); it != curDictionary.end(); it++)
	{
		cout << *it << endl;
	}
}
void hangman::filterByLength(int len)
{
	for(list<string>::iterator it = dictionary.begin(); it != dictionary.end(); it++)
	{
		if((*it).length() == len)
			curDictionary.push_back(*it);
	}
	curWord = curDictionary.front();
}
void hangman::filterByLetter(char l)
{
	list<string> tempList;
	for(list<string>::iterator it = curDictionary.begin(); it != curDictionary.end(); it++)
	{
		if(!strContains(*it,l))
		{
			tempList.push_back(*it);
		}
	}
	if(!tempList.empty())
	{
		curDictionary.clear();
		curDictionary = tempList;
	}
	curWord = curDictionary.front();
}
void hangman::restoreDictionary()
{
	curDictionary.clear();
	for(list<string>::iterator it = dictionary.begin(); it != dictionary.end(); it++)
	{
		curDictionary.push_back(*it);
	}
}
void hangman::printWord()
{
	cout << curWord << endl;
	string dispWord = curWord;
	for(int i = 0; i < dispWord.length(); i++)
	{
		if(!strContains(guesses,dispWord[i]))
			dispWord[i] = '-';
	}
	cout << dispWord << endl;
}
bool hangman::strContains(string str, char g)
{
	for(int i = 0; i < str.length(); i++)
	{
		if(str[i] == g)
			return true;
	}
	return false;
}
void hangman::addGuess(char c)
{
	guesses.push_back(c);
}