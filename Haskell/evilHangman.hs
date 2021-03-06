import System.IO

main :: IO ()
main = do
	inpStr <- readFile "dictionary.txt"
	let s = words inpStr				--read in dictionary as a list of strings
	putStrLn "Enter the length of the word:"
	len <-getLine
	let l = read len :: Int
	let d = filterDictionary l start	--filter the dictionary to have words of length l.
	playGame d [] 10	--start with 10 guesses
	putStrLn ""

----------------Filter Dictionary-----------------
--Takes in an Int and list of Strings, and returns
--only the strings of that Int's length, separated
--by new lines in a single string.
filterDictionary :: Int -> [String] -> [String]
filterDictionary len str = filter (checkStrLen len) str

-- checkStrLen
--   returns True if the length of the string is equal to the integer,
--   else False.
checkStrLen :: Int -> String -> Bool
checkStrLen len str 
	| len == length str = True
	| otherwise         = False

-- elemOfAll
--   returns True if the char is an element of every string in the list,
--   else False.
elemOfAll :: Char -> [String] -> Bool
elemOfAll c []     = False
elemOfAll c (x:[]) = c `elem` x 
elemOfAll c (x:xs)
	| c `elem` x   = elemOfAll c xs
	| otherwise    = False

-------------------Filter Letter------------------
--Takes in a character and a list of strings, and
--returns a new list of strings that do not
--contain that letter.
filterLetter :: Char -> [String] -> [String]
filterLetter c str = filter (c `notElem`) str

-------------------Filter Position----------------
--Takes a string of characters that have been guessed by the user,
--the dictionary list, and the partially revealed word, then returns a new
--list of strings which contains words that match the pattern of
--the parts of the word which has been revealed.
--EX: any words that might fit some pattern like: ---e--a--b
filterPos :: String -> [String] -> String -> [String]
filterPos s strs g = filter (compareStr g s) strs

----------------Compare String--------------------
--Takes in the fully revealed word, the partially revealed word,
--and the list of which letters have been guessed, and returns
--true if the strings match, false if not.
compareStr :: String -> String -> String -> Bool
compareStr _ [] [] = True
compareStr g (a:as) (b:bs)
	| (a == '-') && ((elem b g) == True) = False
	| ((a == '-') || a == b) = compareStr g as bs
	| otherwise = False
compareStr [] (a:as) (b:bs)
	| ((a == '-') || a == b) = compareStr [] as bs
	| otherwise = False

-------------------Display Word-------------------
--Takes in two strings, the first being the word to
--be guessed and the second the list of letters that
--have been guessed by the user, and display either
--'-' for letters that have not been guessed or the
--letters of those which have been guessed.
displayWord :: String -> String -> String
displayWord (w:ws) guesses
	| (elem w guesses) == True = [w] ++ displayWord ws guesses
	| otherwise = "-" ++ displayWord ws guesses
displayWord [] _ = ""

--Gets input from the user. this function will continue
--call itself if input is not valid(not lowercase or
--has already been guessed), then return that char.
getCharInput :: String -> IO Char
getCharInput guesses = do
	letter <- getChar
	if (((elem letter ['a'..'z']) == True) && ((elem letter guesses) == False))
		then return letter
		else do
			inp2 <- getCharInput guesses
			return inp2
	
-------------------Play Game-----------------------
--The main loop for playing the game. It takes in a
--list of strings for the current dictionary, a
--string for the list of letter guesses, and an int
--for the number of guesses remaining.
---------------------------------------------------
playGame :: [String] -> String -> Int -> IO ()
playGame dic guesses remain = do
	let dis = displayWord (head dic) guesses	--display word(covered)
	if (remain == 0)
		then do
			let out = "The word was: " ++ (head dic)	--player has lost, show the word
			putStrLn out
			hm <- readFile "hangman5.txt"
			putStrLn hm
			putStrLn "R.I.P. in peace, Hangman."
		else do
			putStrLn dis
			if ((elem '-' dis) == False)				--player has won
				then do 
					putStrLn "You win this time..."
				else do 								--player has not won, go on with the game
					putStrLn ("Letters guessed so far: " ++ guesses) --show letters guesses so far
					putStrLn (show remain ++ " guesses remain")	--show remaining guesses
					--putStrLn (head dic)				--print uncovered word(for testing)
					putStr "Enter your guess: "
					guess <- getCharInput guesses
					let a = filterLetter guess (filterPos dis dic guesses)
					if a == []
					then playGame dic (guesses ++ [guess]) (remain) --if the filtered list is empty, then the player got a letter right
					else playGame a (guesses ++ [guess]) (remain - 1)	--if the list has elements, then there are words that do not contain that letter.