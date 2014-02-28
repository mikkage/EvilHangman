#include <iostream>
#include "hangman.h"
using namespace std;

int main()
{
	hangman h;
	char input;
	int in;
	cout << "Enter length of word:";
	cin >> in;
	h.filterByLength(in);
	while(true)
	{
		cout << "Enter letter:";
		cin >> input;
		h.filterByLetter(input);
		h.addGuess(input);
		h.printWord();
	}
	cin.get();
	return 0;
}