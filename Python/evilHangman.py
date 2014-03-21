# Evil Hangman
# Reid Anetsberger <ranetsbe>
# Michael Parker <msparker>

#   returns True if c is an element of s, else False
def elem (c, s):
	for x in s:
		if c == x:
			return True
	return False

#   elem for a two-dimensional list
#   returns true if c is an element of every list
def elemAll (c, strs):
	for s in strs:
		if not elem(c, s):
			return False
	return True

#   filter a list by string length
def filterLen (n, l):
	new = []
	for s in l:
		if n == len(s):
			new.append(s)
	return new

#   filter a list of strings by a character
#   returns a list of strings that do not contain the character
def filterLetter (c, strs):
	new = []
	for s in strs:
		if not elem(c, s):
			new.append(s)
	return new

#   reveal the guessed letter in the secret word
def reveal (c, secret, word):
	pos = 0;
	for letter in word:
		if c == letter:
			secret = secret[:pos] + c + secret[pos + 1:]
		pos += 1 
	return secret

#   returns a list of words from l with c as the nth letter
def filterPos (c, n, l):
	new = []
	for word in l:
		if c == word[n]:
			new.append(word)
	return new

#   filter the words in the dictionary by position of letters
def filterLetterPos (secret, dictionary):
	new = dictionary
	position = 0
	for letter in secret:
		if letter != '_':
			new = filterPos(letter, position, new)
		position += 1
	return new

# main
# read dictionary file, throw away trailing newlines
words = list(open("dictionary.txt", 'r').read().split('\n'))

# filter the dictionary by string lenth
strLen = int(input("Enter the length of the word: "))
words = filterLen(strLen, words)

# setup the secret word that we will build
secret = ''
# guessed character
guess = ''
guesses = ""
for i in range(strLen):
	secret += '_'
guessCount = 0
# loop until the 'secret word' is complete or the player runs out of guesses
while elem('_', secret) and guessCount < 10:
	print(secret)
	print("Guessed so far: " + guesses)
	guess = input("Guess a character: ")
	if elem(guess, guesses):
		print ("You already guessed " + guess + ".  Try again.")
	else:
		guesses += guess
		if elemAll(guess, words):
			# give the user a char
			pick = words[0]
			secret = reveal(guess, secret, pick)
			words = filterLetterPos(secret, words)
		else:
			# filter the char
			guessCount += 1
			words = filterLetter(guess, words)
if guessCount == 10:
	print("You Lose")
	gfx = open("gfx.txt", 'r').read()
	print(gfx)
else:
	print("The word was \"" + secret + "\"")
	print("You win this time...")