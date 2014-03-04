#pragma once
#include "hangman.h"
hangman::hangman()
{
	//initialize dictionary list, load full dictionary.
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
	cur = new list<string>;	//initialize dynamic dictionary.
}
void hangman::showDic()	//Prints out filtered dictionary
{
	for(list<string>::iterator it = cur->begin(); it != cur->end(); it++)
	{
		cout << *it << endl;
	}
}
void hangman::filterByLength(int length)	//Filters the dynamic dictionary to contain words of only a certain length.
{
	delete cur;	//Clear current dictionary, then initialize a new empty one.
	cur = new list<string>;
	for(list<string>::iterator it = dictionary.begin(); it != dictionary.end(); it++)
	{
		if((*it).length() == length)
			cur->push_back(*it);
	}
	curWord = cur->front();	//Set current word to the head of the list.
}
void hangman::filterByLetter(char l)	//Filters the dynamic dictionary to only contain words which do not contain
										//the given letter, if possible
{
	list<string> *tempList = new list<string>;
	for(list<string>::iterator it = cur->begin(); it != cur->end(); it++)
	{
		if(!strContains(*it,l))
		{
			tempList->push_back(*it);	//Go through dynamic dictionary, and add any words that do not have the given
		}								//character to the temp dictionary.
	}
	if(!tempList->empty())				//If the temp dictionary is not empty, then there are words which fit the criteria
	{
		delete cur;			//Clear current dynamic dictionary
		cur = tempList;		//Set the dynamic dictionary to the one which has just been made.
	}						//If the temp dictionary is empty, that means there are no words which fit the criteria, and we
							//continue to use the original version of the dynamic dictionary
	curWord = cur->front();	//Update current word.
}
void hangman::filterByPos()	//Filters out any words which do not fit a partially revealed pattern.
{
	string curReveal = getPrintWord();
	bool doPosFilter = false;
	for(int i = 0; i < curReveal.length(); i ++)	//Check to see if the current word has any letters revealed(e.g. not "------")
	{
		if(curReveal[i] != '-')
			doPosFilter = true;
	}								//If the current word only contains '-', then we do not have to filter by position
	if(doPosFilter)					//If any letters are revealed, then we must make sure all words that do not fit that pattern are removed.
	{
	list<string> *tempList = new list<string>;
	for(list<string>::iterator it = cur->begin(); it != cur->end(); it++)	//Go through entire dynamic dictionary and determine which words to add.
	{
		bool add = true;
		for(int i = 0; i < (*it).length(); i++)
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
				if((*it)[i] != curReveal[i])		//If the two words do not have the same letter at the same position, then it does not get
					add = false;					//added to the temp dictionary.
			}
		}
		if(add)										//If add is still true, then the word has passed all of the tests and can be added to the
			tempList->push_back(*it);				//temp dictionary
	}
	if(!tempList->empty())							//Check to see if the temp dictionary is empty/
	{
		delete cur;									//If not, then we can replace the current dynamic dictionary to the temp dictionary.
		cur = tempList;								//If it is, then we have to continue to use the original dynamic dictionary.
	}
	curWord = cur->front();							//Update current word.
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
	delete cur;
	cur = new list<string>;
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
			if(strContains(showWord,guess))		//If the displayed word contains the guessed letter, the guess was correct and
				remain++;						//a guess is refunded.

			cout << "You have " << remain << " guesses left." << endl;
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