#include "hangman.h"
hangman::hangman()
{
	//initialize dictionary list
	string in;
	fstream fin;
	fin.open("dictionary.txt");
	while(!fin.eof())
	{
		fin >> in;
		dictionary.push_back(in);
		//curDictionary.push_back(in);
	}
	fin.close();
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
		curDictionary = tempList;
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
	string dispWord = curWord;
	std::size_t found = dispWord.find_first_of(guesses);
	while(found != std::string::npos)
	{
		dispWord[found] = '-';
		found = dispWord.find_first_of(guesses,found+1);
	}
	cout << dispWord;
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
void hangman::setGuesses(string g)
{
	guesses = g;
}
void hangman::setWord(string w)
{
	curWord = w;
}