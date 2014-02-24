#include <iostream>
#include "hangman.h"
using namespace std;

int main()
{
	hangman h;
	h.filterByLength(5);
	h.showDic();

	h.filterByLetter('f');
	h.showDic();

	h.filterByLetter('a');
	h.showDic();

	cin.get();
	return 0;
}