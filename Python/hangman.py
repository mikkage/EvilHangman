# Evil Hangman
# python
# start 3:20pm

# some useful functions

# 	returns True if c is an element of s, else False
def elem (c, s):
	for x in s:
		if c == x:
			return True
	return False

#	elem with binary search (only works on sorted list)
def elemR (x, xs):
	if len(xs) == 0:
		return False
	pivot = len(xs) // 2
	if x == xs[pivot]:
		return True
	elif x < xs[pivot]:
		return elemR(x, xs[:pivot])
	else:
		return elemR(x, xs[pivot + 1:])

#	elem for a two-dimensional list
#	returns true if c is an element of every list
def elemAll (c, strs):
	for s in strs:
		if not elem(c, s):
			return False
	return True

#	filter a list by string length
def filterLen (n, l):
	new = []
	for s in l:
		if n == len(s):
			new.append(s)
	return new

#	filter a list of strings by a character
#	returns a list of strings that do not contain the character
def filterChar (c, strs):
	new = []
	for s in strs:
		if not elem(c, s):
			new.append(s)
	return new

def reveal (c, secret, word):
	pos = 0;
	for letter in word:
		if c == letter:
			secret = secret[:pos] + c + secret[pos + 1:]
		pos += 1 
	return secret

# main
# read dictionary file, throw away trailing newlines
words = list(open("dictionary.txt", 'r').read().split('\n'))

# filter the dictionary by string lenth
strLen = int(input("Enter the length of the word: "))
words = filterLen(strLen, words)

# setup the secret word that we will build
secret = ''
guess = ''
for i in range(strLen):
	secret += '_'

guessCount = 0
while elem('_', secret) and guessCount < 30:
	print(secret)
	guess = input("Guess a character: ")
	if elemAll(guess, words):
		# give the user a char
		pick = words[0]
		secret = reveal (guess, secret, pick)
	else:
		# filter the char
                guessCount += 1
		words = filterChar(guess, words)

