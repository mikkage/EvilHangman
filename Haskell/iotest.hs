import System.IO

main :: IO ()
main = do
	inpStr <- readFile "dictionary.txt"
	let s = words inpStr

	-- insane hangman graphics
	-- 6 files (0 - 5)
	-- hangman0 is start, hangman5 is end
	-- could add more if 5 guesses isnt enough
	inpStr <- readFile "hangman5.txt"
	let hangman = inpStr
	putStrLn hangman

	putStrLn "Enter the length of the word:"
	len <-getLine
	let l = read len :: Int

	let d = filterDictionary l s

	playGame d [] 30	--start with 30 guesses, just for testing

	putStrLn ""

	--putStrLn "Enter a character to filter out:"
	--letter <- getChar
	
	--let o = "Words of length " ++ len ++ " filtered out from dictionary.txt to --out.txt"
	--putStrLn o
	--let o1 = "Shortest word length: " ++ show (minimum (map length s))
	--putStrLn o1
	--let o2 = "Longest word length: " ++ show (maximum (map length s))
	--putStrLn o2
	
	--let out = (filterDictionary l s)
	--writeFile "out.txt" (unwords out)
	--writeFile "outfiltered.txt" (unwords (filterLetter letter out))

--------------------------------------------------
----------------Filter Dictionary-----------------
--Takes in an Int and list of Strings, and returns
--only the strings of that Int's length, separated
--by new lines in a single string.
--------------------------------------------------
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

--------------------------------------------------
-------------------Filter Letter------------------
--Takes in a character and a list of strings, and
--returns a new list of strings that do not
--contain that letter.
--------------------------------------------------
filterLetter :: Char -> [String] -> [String]
filterLetter c str = filter (c `notElem`) str

filterPos :: String -> [String] -> [String]
filterPos s strs = filter (compareStr s) strs

compareStr :: String -> String -> Bool
compareStr [] [] = True
compareStr (a:as) (b:bs)
	| a == '-' || a == b = compareStr as bs
	| otherwise          = False

--------------------------------------------------
-------------------Display Word-------------------
--Takes in two strings, the first being the word to
--be guessed and the second the list of letters that
--have been guessed by the user, and display either
--'-' for letters that have not been guessed or the
--letters of those which have been guessed.
--------------------------------------------------
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
	
---------------------------------------------------
-------------------Play Game-----------------------
--The main loop for playing the game. It takes in a
--list of strings for the current dictionary, a
--string for the list of letter guesses, and an int
--for the number of guesses remaining.
---------------------------------------------------
playGame :: [String] -> String -> Int -> IO ()
playGame dic guesses remain = do
	let dis = displayWord (head dic) guesses	--display word(covered)
	if ((elem '-' dis) == False)
		then do 
			putStrLn dis
			putStrLn "You win this time..."
		else do
			putStrLn ("Letters guessed so far: " ++ guesses) --show letters guesses so far
			putStrLn (show remain ++ " guesses remain")	--show remaining guesses
			putStrLn (head dic)				--print uncovered word(for testing)
			putStrLn dis
			putStr "Enter your guess: "
			guess <- getCharInput guesses
			let a = filterLetter guess (filterPos dis dic)
			if a == []
			then playGame dic (guesses ++ [guess]) (remain - 1)
			else playGame a (guesses ++ [guess]) (remain - 1)

-- qsort
--   quicksort in 3 lines (not in place)
qsort :: (Ord a) => [a] -> [a]
qsort []     = []
qsort (x:xs) = qsort (filter (< x) xs) ++ [x] ++ qsort (filter (>= x) xs)
