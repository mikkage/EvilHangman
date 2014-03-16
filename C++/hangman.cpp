#pragma once
#include <iostream>
#include "hangman.h"
hangman::hangman()
{
	dict = new string[150000];
	curDict = new string[100000];
	dictLen = 0;
	string in;
	fstream fin;
	fin.open("dictionary.txt");
	cout << "Loading dictionary...";
	while(!fin.eof())
	{
		fin >> in;
		//dictionary.push_back(in);
		dict[dictLen] = in;
		dictLen++;
	}
	fin.close();
	cout << endl << "Done"<< endl;
	curLen = 0;
}
void hangman::showDic()	//Prints out filtered dictionary
{
	/*
	for(list<string>::iterator it = cur->begin(); it != cur->end(); it++)
	{
		cout << *it << endl;
	}*/
	for(int i = 0; i < curLen; i++)
	{
		cout << dict[i] << endl;
	}
}
void hangman::filterByLength(int length)	//Filters the dynamic dictionary to contain words of only a certain length.
{
	curLen = 0;
	for(int i = 0; i < dictLen; i++)
	{
		if(dict[i].length() == length)
		{
			curDict[curLen] = dict[i];
			curLen++;
		}
	}
	curWord = curDict[0];
}
void hangman::filterByLetter(char l)	//Filters the dynamic dictionary to only contain words which do not contain
										//the given letter, if possible
{
	string *dict1 = new string[100000];
	int dict1Len = 0;

	for(int i = 0; i < curLen; i++)
	{
		if(!strContains(curDict[i], l))
		{
			dict1[dict1Len] = curDict[i];
			dict1Len++;
		}
	}
	if(dict1Len > 0)
	{
		for(int i = 0; i < dict1Len; i++)
		{
			curDict[i] = dict1[i];
		}
		curLen = dict1Len;
	}
	curWord = curDict[0];
}
void hangman::filterByPos()	//Filters out any words which do not fit a partially revealed pattern.
{
	list<string> *tempList = new list<string>;
	string *dict1 = new string[100000];
	int dict1Len = 0;
	string curReveal = getPrintWord();
	bool doPosFilter = false;
	for(int i = 0; i < curReveal.length(); i ++)	//Check to see if the current word has any letters revealed(e.g. not "------")
	{
		if(curReveal[i] != '-')
			doPosFilter = true;
	}								//If the current word only contains '-', then we do not have to filter by position
	if(doPosFilter)					//If any letters are revealed, then we must make sure all words that do not fit that pattern are removed.
	{
	for(int j = 0; j < curLen; j++)
	{
		bool add = true;
		for(int i = 0; i < curDict[j].length(); i++)
		{
			if(curReveal[i] == '-')
			{
				if(strContains(guesses,curWord[i]))	//If the current character is '-', then we have to check to see if the revealed version
				{									//has an exposed character at that same position.
					add = false;					//If it does, then it does not fit the pattern and should not be added to the temp dictionary.
				}
			}
			else									//Otherwise, the current character is a letter.
			{
				//If the two words do not have the same letter at the same position, then it does not get
				if(curDict[j][i] != curReveal[i])
					add = false;					//added to the temp dictionary.
			}
		}
		if(add)										//If add is still true, then the word has passed all of the tests and can be added to the
		{
			dict1[dict1Len] = curDict[j];
			dict1Len++;
		}
	}
	if(dict1Len != 0)
	{
		for(int i = 0; i < dict1Len; i++)
		{
			curDict[i] = dict1[i];
		}
		curLen = dict1Len;
	}
	curWord = curDict[0];
	}
}
bool hangman::strContains(string s, char g)	//Returns true if the given string contains the given character, false if it does not.
{
	for(int i = 0; i < s.length(); i++)
	{
		if(s[i] == g)
			return true;
	}
	return false;
}
void hangman::restoreDictionary()	//Empties out the dynamic dictionary.
{
	//delete cur;
	//cur = new list<string>;
	curLen = 0;
}
void hangman::printWord()	//Prints out the current word, with any guessed letters exposed.
{
	//cout << curWord << endl;	//TESTING
	string dispWord = curWord;
	for(int i = 0; i < dispWord.length(); i++)
	{
		if(!strContains(guesses,dispWord[i]))
			dispWord[i] = '-';
	}
	cout << dispWord << endl;
	showWord = dispWord;
}
void hangman::playGame()	//Method to play the game.
{
	bool won = false;
	bool playAgain;

	do
	{
		remain = 25;		//Initialize the number of guesses
		restoreDictionary();	//Clear dynamic dictionary
		guesses = "";			//Clear guessed letters.

		char guess;
		int len;

		cout << "Enter the length of the word:";
		cin >> len;

		filterByLength(len);	//Filter out words of a certain length
		printWord();

		while (remain > 0)		//Main loop for making guesses.
		{
			string testWin = getPrintWord();
			if(!strContains(testWin, '-'))	//Check to see if the user has won(displayed string does not contain any '-')
				won = true;
			if(won)	//If you have revealed the full word, break out of the while loop.
				break;
			bool validChar = false;

			filterByPos();	//Filter by position in case any letters are revealed. 
			while(!validChar)
			{
				cout << "Enter your guess:";
				cin >> guess;
				if(!strContains(guesses,guess))	//Make sure the letter has not been guessed already.
				{
					validChar = true;
					guesses.push_back(guess);	//Append guessed character to end of guesses string.
					remain--;					//Used up a guess.
				}
			}
			filterByLetter(guess);				//Filter out words with the guessed letter.
			if(strContains(getPrintWord(),guess))		//If the displayed word contains the guessed letter, the guess was correct and
				remain++;						//a guess is refunded.
			cout << "You have " << remain << " guesses left." << endl << endl;
			cout << "Guesses so far: " << intersperse(guesses,' ') << endl;
			printWord();
		}
		if(!won)	//If you use up the guesses without revealing the full word, you lost.
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
string hangman::getPrintWord()	//Returns the displayed word, which can be revealed partially or fully.
{
	string dispWord = curWord;
	for(int i = 0; i < dispWord.length(); i++)
	{
		if(!strContains(guesses,dispWord[i]))
			dispWord[i] = '-';
	}
	return dispWord;
}
string hangman::intersperse(string s, char c)
{
	string retrnVal = "";
	for(int i = 0;i < s.length(); i++)
	{
		retrnVal.push_back(s[i]);
		retrnVal.push_back(c);
	}
	return retrnVal;
}