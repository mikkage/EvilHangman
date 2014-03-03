#pragma once
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
	cur = new list<string>;
}
void hangman::showDic()
{
	for(list<string>::iterator it = cur->begin(); it != cur->end(); it++)
	{
		cout << *it << endl;
	}
}
void hangman::filterByLength(int length)
{
	delete cur;
	cur = new list<string>;
	for(list<string>::iterator it = dictionary.begin(); it != dictionary.end(); it++)
	{
		if((*it).length() == length)
			cur->push_back(*it);
	}
	curWord = cur->front();
}
void hangman::filterByLetter(char l)
{
	list<string> *tempList = new list<string>;
	for(list<string>::iterator it = cur->begin(); it != cur->end(); it++)
	{
		if(!strContains(*it,l))
		{
			tempList->push_back(*it);
		}
	}
	if(!tempList->empty())
	{
		delete cur;
		cur = tempList;
	}
	curWord = cur->front();
}
void hangman::filterByPos()
{
	string curReveal = getPrintWord();
	bool doPosFilter = false;
	for(int i = 0; i < curReveal.length(); i ++)
	{
		if(curReveal[i] != '-')
			doPosFilter = true;
	}
	if(doPosFilter)
	{
	list<string> *tempList = new list<string>;
	for(list<string>::iterator it = cur->begin(); it != cur->end(); it++)
	{
		bool add = true;
		for(int i = 0; i < (*it).length(); i++)
		{
			if(curReveal[i] == '-')
			{
				if(strContains(guesses,curWord[i]))
				{
					add = false;
				}
			}
			else
			{
				if((*it)[i] != curReveal[i])
					add = false;
			}
		}
		if(add)
			tempList->push_back(*it);
	}
	if(!tempList->empty())
	{
		delete cur;
		cur = tempList;
	}
	curWord = cur->front();
	}
}
bool hangman::strContains(string s, char g)
{
	for(int i = 0; i < s.length(); i++)
	{
		if(s[i] == g)
			return true;
	}
	return false;
}
void hangman::restoreDictionary()
{
	//curDictionary.clear();
	delete cur;
	cur = new list<string>;
	for(list<string>::iterator it = dictionary.begin(); it != dictionary.end(); it++)
	{
		cur->push_back(*it);
	}
}
void hangman::printWord()
{
	//cout << curWord << endl;
	string dispWord = curWord;
	for(int i = 0; i < dispWord.length(); i++)
	{
		if(!strContains(guesses,dispWord[i]))
			dispWord[i] = '-';
	}
	cout << dispWord << endl;
	showWord = dispWord;
}
void hangman::playGame()
{
	bool won = false;
	bool playAgain;
	do
	{
		remain = 25;
		restoreDictionary();
		guesses = "";

		char guess;
		int len;

		cout << "Enter the length of the word:";
		cin >> len;
		filterByLength(len);
		printWord();

		while (remain > 0)
		{
			string testWin = getPrintWord();
			if(!strContains(testWin, '-'))
				won = true;
			if(won)
				break;
			bool validChar = false;
			filterByPos();
			while(!validChar)
			{
				cout << "Enter your guess:";
				cin >> guess;
				if(!strContains(guesses,guess))
				{
					validChar = true;
					guesses.push_back(guess);
					remain--;
				}
			}
			filterByLetter(guess);
			if(strContains(showWord,guess))
				remain++;

			cout << "You have " << remain << " guesses left." << endl;
			printWord();
		}
		if(!won)
		{
			cout << "You suck." << endl;
			cout << "The word was: " << curWord << endl;
		}
		else cout << "H4XX0r!!1 You won." << endl;
		cout << "Play again?(y/n)";
		cin >> guess;

		if(guess == 'y' || guess == 'Y')
		{
			playAgain = true;
			won = false;
		}
		else playAgain = false;
	} while (playAgain);
}
string hangman::getPrintWord()
{
	string dispWord = curWord;
	for(int i = 0; i < dispWord.length(); i++)
	{
		if(!strContains(guesses,dispWord[i]))
			dispWord[i] = '-';
	}
	return dispWord;
}